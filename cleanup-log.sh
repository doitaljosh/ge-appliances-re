#!/bin/bash

cut -c 9- $1 | \
cut -c -51 | \
cut --complement -c25-26 | \
sed -e 's/e3 e2/e3 \ne2/g' > \
cleaned-$1
