# Create compressed disk partition image
sudo dd conv=noerror,sync status=progress bs=8M if=/dev/sda8 | gzip -1c > "/home/tduyduc/Documents/Disk Image of sda8 (2018-06-26 1849).img.gz"

# Compress an existing image
gzip -1c < "/home/tduyduc/Documents/Disk Image of sda4 (2018-05-29 1452).img" > "/home/tduyduc/Documents/Disk Image of sda4 (2018-05-29 1452).img.gz"

# Restore from a compressed disk partition image
gzip -dc "/home/tduyduc/Documents/Disk Image of sda4 (2018-05-29 1452).img.gz" | sudo dd conv=noerror,sync status=progress bs=8M of=/dev/sda8

# Create squashfs image from a folder
mksquashfs /home/tduyduc/Pictures/ /home/tduyduc/Documents/Pictures.squashfs -b 4K

# Repeat image creation until copying succeeds, in case the disc is unreadable at some point, stopping dd
until dd if=/dev/sr0 of="/home/tduyduc/Documents/DVD Image.iso" bs=8M status=progress; do echo "Trying again in 1 second. Press Ctrl+C to cancel."; sleep 1; done
