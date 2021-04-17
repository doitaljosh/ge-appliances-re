#!/bin/bash

cut -c 9- $1 | \
cut -c -51 | \
cut --complement -c25-26 | \
sed -e 's/e3 e2/e3 \ne2/g' > \
sed -e 's/c6 e2/c6 \ne2/g' > \
sed -e 's/c7 e2/c7 \ne2/g' > \
cleaned-$1
