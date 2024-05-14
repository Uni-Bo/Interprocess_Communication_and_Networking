
#!/bin/bash

# FTP server details
HOST="16.10.99.103"
USER="student"
PASSWORD="your_password"
REMOTE_FILE="UDP Socket Programming_2.pdf"
LOCAL_FILE="UDP_Socket_Programming_2.pdf"

# Connect to FTP server
ftp -n $HOST <<END_SCRIPT
quote USER $USER
quote PASS $PASSWORD

# Set transfer mode to ASCII
ascii

# Enable hash mark printing
hash

# Download file
get "$REMOTE_FILE" "$LOCAL_FILE"

quit
END_SCRIPT

