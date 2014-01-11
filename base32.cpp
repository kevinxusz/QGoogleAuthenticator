#include "base32.h"

int Base32::base32_encode(QString *data, QString *result, int bufferSize)
{
    int count = 0;

    int buffer = data->at(0).toLatin1();
    int next = 1;
    int bitsLeft = 8;
    while (count < bufferSize && (bitsLeft > 0 || next < 20)) // 10 secret length
    {
        if (bitsLeft < 5)
        {
            if (next < 20)
            {
                buffer <<= 8;
                buffer |= data->at(next++).toLatin1() & 0xFF;
                bitsLeft += 8;
            }
            else
            {
                int pad = 5 - bitsLeft;
                buffer <<= pad;
                bitsLeft += pad;
            }
        }
        int index = 0x1F & (buffer >> (bitsLeft - 5));
        bitsLeft -= 5;
        result->replace(count++, 1, "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"[index]);
    }
    if (count < bufferSize)
        result->replace(count, 1, QChar('\000'));

    return count;
}

int Base32::base32_decode(const quint8 *encoded, quint8 *result, int bufSize)
{
    int buffer = 0;
    int bitsLeft = 0;
    int count = 0;

    for (const quint8 *ptr = encoded; count < bufSize && *ptr; ++ptr) {
        quint8 ch = *ptr;

        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '-') {
            continue;
        }

        buffer <<= 5;

        // Deal with commonly mistyped characters
        if (ch == '0') {
            ch = 'O';
        } else if (ch == '1') {
            ch = 'L';
        } else if (ch == '8') {
            ch = 'B';
        }

        // Look up one base32 digit
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            ch = (ch & 0x1F) - 1;
        } else if (ch >= '2' && ch <= '7') {
            ch -= '2' - 26;
        } else {
            return -1;
        }

        buffer |= ch;
        bitsLeft += 5;

        if (bitsLeft >= 8) {
            result[count++] = buffer >> (bitsLeft - 8);
            bitsLeft -= 8;
        }
    }

    if (count < bufSize) {
        result[count] = '\000';
    }

    return count;
}
