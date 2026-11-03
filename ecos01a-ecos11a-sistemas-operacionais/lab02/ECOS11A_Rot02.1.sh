#!/bin/bash

# Função para verificar o uso de CPU
verificar_cpu() {
    top -n 1 | grep "Cpu(s)"
}

# Chamada da função
verificar_cpu
