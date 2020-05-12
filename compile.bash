#!/bin/bash
touch previous
while true; do
    sleep 1s
    git diff src/nn-training > current
    cmp --silent current previous || npm run compile
    cat current > previous
done;