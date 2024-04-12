#!/bin/bash

paralelo_caminho="../bin/paralelo"
sequencial_caminho="../bin/sequencial"

if [ ! -f "$paralelo_caminho"  ]; then
    echo "Binário de solução paralela não encontrado: $paralelo_caminho"

    exit 1
fi

if [ ! -f "$paralelo_caminho"  ]; then
    echo "Binário de solução sequencial não encontrado: $sequencial_caminho"

    exit 1
fi

for i in {1..3}; do
    echo "Testando paralelo $i"

    time $paralelo_caminho | wc -l
done

for i in {1..3}; do
    echo "Testando sequencial $i"

    time $sequencial_caminho | wc -l
done
