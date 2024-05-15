#!/bin/bash

tasks=()


# Add commands to the tasks array
tasks+=("wget https://ftp.psnc.pl/linux/linuxmint/iso/stable/21.3/linuxmint-21.3-cinnamon-64bit.iso")
tasks+=("sleep infinity")
tasks+=("ping -c 10 pg.edu.pl")
tasks+=("find $HOME -type d -name 'lab3'")


# Run tasks in parallel
for task in "${tasks[@]}"; do
    $task &
done

for pid in pgrep -P $$; do
    wait $pid
done
