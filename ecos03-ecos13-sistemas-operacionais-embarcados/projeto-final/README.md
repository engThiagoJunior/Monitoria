# ECOS03 - Projeto Final 2024.2
## Sistema de Controle de Iluminação Inteligente

### 👥 Desenvolvedores
- **Gabriel Fazion dos Santos**
- **Thiago de Oliveira Sousa Júnior**

### 📋 Descrição do Projeto
Sistema de controle de iluminação inteligente desenvolvido para a placa RedPill (STM32F103). A proposta da disciplina cita o FreeRTOS; a implementação usa a API CMSIS-RTOS com o kernel Keil RTX. Oito tarefas gerenciam os padrões de iluminação, os botões, o potenciômetro, o buzzer e o display LCD.

### 🎯 Funcionalidades Implementadas

#### Padrões de Iluminação:
- **Função 01**: Piscar alternado entre LEDs pares e ímpares
- **Função 02**: Piscar seguindo código Gray
- **Função 03**: Barra de progresso controlada por potenciômetro
- **Função 04**: Feedback visual e sonoro com buzzer

#### Controles:
- **Botões C, D, E, F**: Seleção de modos de funcionamento
- **Botões Y, A, X, B, L, M, N**: Controle de velocidade
- **Display**: Mostrador de estado e teclas pressionadas

### 🛠️ Pré-requisitos

#### Hardware:
- Placa RedPill (STM32F103)
- Cabo USB para programação
- Computador com porta USB

#### Software:
- [STM32 ST-LINK Utility](https://www.st.com/en/development-tools/stsw-link004.html#get-software)
- [Keil uVision5](https://www.keil.com/download/product/)

### 🚀 Como Executar o Projeto

#### Clone do repositório
```bash
git clone https://github.com/engThiagoJunior/Monitoria.git
cd Monitoria/ecos03-ecos13-sistemas-operacionais-embarcados/projeto-final/TF_SOE
```

#### Configuração e Upload:

- Abra `final.uvprojx` no Keil uVision;
- Compile o projeto (F7);
- Conecte a placa RedPill via USB;
- Grave o código na placa;
- Pressione o botão de reset na placa;
- O sistema iniciará automaticamente.

## 🎮 Como Usar

### Seleção de Modo:
* **Botão C:** Função 01 (LEDs pares/ímpares)
* **Botão D:** Função 02 (Código Gray)
* **Botão E:** Função 03 (Potenciômetro)
* **Botão F:** Função 04 (Sonoro/Mudo)

### Controle de Velocidade:
* **Botão Y:** Dobra velocidade
* **Botão A:** Metade da velocidade
* **Botão X:** Velocidade padrão
* **Botão B:** Velocidade por potenciômetro
* **Botão L:** Período de 500 ms
* **Botão M:** Período de 2000 ms
* **Botão N:** Período de 10000 ms

---

## 🔧 Solução de Problemas

* **Problema:** Placa não é detectada
    * **Solução:** Verificar drivers ST-Link e cabo USB
* **Problema:** Erro de compilação no Keil
    * **Solução:** Verificar configuração do projeto para STM32F103
* **Problema:** LEDs não acendem
    * **Solução:** Verificar se o código foi gravado corretamente
