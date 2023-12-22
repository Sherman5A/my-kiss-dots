#!/bin/sh

help() {
    echo "Le help menu"
    echo "There are no options"
}

change_bri() {

    echo $1

    current_bri=`cat /sys/class/backlight/amdgpu_bl0/brightness`
    low_range=0
    high_range=255

    new_bri=$(expr $current_bri + $1)

    if [ $new_bri -lt $low_range ]; then
        new_bri=0
    elif [ $new_bri -gt $high_range ]; then
        new_bri=255
    fi

    echo $new_bri > /sys/class/backlight/amdgpu_bl0/brightness
    cat /sys/class/backlight/amdgpu_bl0/brightness
}

# Process Arguments

case $1 in
    -h)
        help
        exit;;
    *)
        change_bri $1
        exit;;

esac
done

exit

