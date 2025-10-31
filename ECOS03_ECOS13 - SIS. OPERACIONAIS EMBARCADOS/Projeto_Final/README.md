# ECOS03 - Projeto Final 2024.2
## Sistema de Controle de Iluminação Inteligente

### 👥 Desenvolvedores
- **Gabriel Fazion do Santos**
- **Thiago de Oliveira Sousa Júnior**

### 📋 Descrição do Projeto
Sistema de controle de iluminação inteligente desenvolvido para a placa STM32F103 (RedPill) utilizando FreeRTOS. O sistema gerencia múltiplos padrões de iluminação com controle por horários, botões e sensores.

### 🎯 Funcionalidades Implementadas

#### Padrões de Iluminação:
- **Função 01**: Piscar alternado entre LEDs pares e ímpares
- **Função 02**: Piscar seguindo código Gray
- **Função 03**: Barra de progresso controlada por potenciômetro
- **Função 04**: Feedback visual e sonoro com buzzer

#### Controles:
- **Botões C, D, E, F**: Seleção de modos de funcionamento
- **Botões Y, A, X, B**: Controle de velocidade
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

#### Opção 1: Clone do Git
```bash
git clone [https://github.com/engThiagoJunior/Monitoria/tree/main/ECOS03_ECOS13%20-%20SIS.%20OPERACIONAIS%20EMBARCADOS/Projeto_Final]
```
#### Opção 2: Download Manual
- Baixe o arquivo main.c e outros arquivos necessários do repositório

#### Configuração e Upload:

- Abra o Keil uVision;
- Crie um novo projeto ou abra o projeto existente;
- Adicione o arquivo main.c ao projeto;
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

---

## 🔧 Solução de Problemas

* **Problema:** Placa não é detectada
    * **Solução:** Verificar drivers ST-Link e cabo USB
* **Problema:** Erro de compilação no Keil
    * **Solução:** Verificar configuração do projeto para STM32F103
* **Problema:** LEDs não acendem
    * **Solução:** Verificar se o código foi gravado corretamente

---

## 📞 Suporte
Para dúvidas sobre este projeto específico, entre em contato com os desenvolvedores listados acima.