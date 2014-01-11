#include "qgoogleauthenticator.h"

QString QGoogleAuthenticator::getCode(QByteArray secret, quint64 time)
{
    QString challenge;
    quint64 current;
    if (time == 0)
    {
        time = QDateTime::currentDateTime().toTime_t();
        current = qToBigEndian(time / 30);
    }
    else
        current = time;



    int secretLen = (secret.length() + 7) / 8 * 5;
    quint8 key[100];
    int res = Base32::base32_decode(reinterpret_cast<const quint8 *>(secret.constData()), key, secretLen);
    QByteArray hmac = HMAC::hmacSha1(QByteArray(reinterpret_cast<const char *>(key), res), QByteArray((char*)&current, sizeof(current)));

    int offset = (hmac[hmac.length() - 1] & 0xf);
    int binary =
            ((hmac[offset] & 0x7f) << 24)
            | ((hmac[offset + 1] & 0xff) << 16)
            | ((hmac[offset + 2] & 0xff) << 8)
            | (hmac[offset + 3] & 0xff);

    int password = binary % 1000000;
    return QString("%1").arg(password, 6, 10, QChar('0'));
}

bool QGoogleAuthenticator::checkCode(QString code, QByteArray secret)
{
    quint64 time = 0;
    quint64 current = 0;
    for (int i = -1; i <= 1; i++)
    {
        time = QDateTime::currentDateTime().toTime_t() / 30 + i;
        current = qToBigEndian(time);
        if (code == getCode(secret, current))
            return true;
    }
    return false;
}

QString QGoogleAuthenticator::generate_secret()
{
    qsrand(QTime::currentTime().msec());
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    QString secret = "";
    for(int i = 0; i < SECRET_LENGTH; i++)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        secret.append(nextChar);
    }
    QString result;
    Base32::base32_encode(&secret, &result, secret.length());
    return result;
}
