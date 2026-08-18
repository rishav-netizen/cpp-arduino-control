#include <fcntl.h>  // for open() and flags like O_RDWR
#include <iostream> // for the normal stuff
#include <termios.h> // for serial port configurations
#include <unistd.h> // for read() and close()
#include <cctype>

using namespace std;

int main() {
    const char* port = "/dev/cu.usbmodem1201";

    // opens the arduino port if not found then returns -1
    // UNIX systems treat ports as files so we open in read write mode
    int serial = open(port, O_RDWR | O_NOCTTY);

    if (serial == -1) { 
        cerr << "Could not open serial port\n";
        return 1;
    }

    termios tty{}; // macOS structure containing the data of serial device i.e here arduino

    if (tcgetattr(serial, &tty) != 0) { // gets the attributes of the serial connection we attached and put into tty
        cerr << "Could not get serial port settings\n";
        close(serial);
        return 1;
    }

    // set the baud rate which is same as in the arduino file, both for input and output
    cfsetispeed(&tty, B9600); 
    cfsetospeed(&tty, B9600);

    // 8N1
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE; 
    tty.c_cflag |= CS8; // 8 BITS
    tty.c_cflag &= ~PARENB; // NO parity
    tty.c_cflag &= ~CSTOPB; // 1 stop bit 
    // enable receiving

    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_iflag = 0;

    tcsetattr(serial, TCSANOW, &tty);

    // arduino may reset after serial info is taken
    sleep(2);

    while (true) {
        char input;
        cout << "Enter command 'R' or 'G' or 'B' or 'Q'(to quit): ";
        cin >> input;
        input = toupper(input);

        if (input == 'Q')
        {
            break;
        }
        if (input == 'R' or input == 'G' or input == 'B')
        {
            write(serial, &input, 1);
        }
        else
        {
            cout << "Invalid Input\n";
        }
    }

    close(serial);

    return 0;
}