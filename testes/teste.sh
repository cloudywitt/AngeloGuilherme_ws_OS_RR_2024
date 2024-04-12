#!/bin/bash

for i in {1..3}; do
    echo "Testando paralelo $i"

    time ../bin/paralelo | wc -l
done

for i in {1..3}; do
    echo "Testando sequencial $i"

    time ../bin/sequencial | wc -l
done
