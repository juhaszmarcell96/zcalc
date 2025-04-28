#!/bin/bash

for img in *.png; do
    convert "$img" -gravity north -background none -splice 0x2 "$img"
done