# ECOP04 & ECOP14 - Programação Embarcada

Esta pasta contém materiais de apoio para as disciplinas **ECOP04 - Programação Embarcada** e **ECOP14 - Laboratório de Programação Embarcada**.

## ⚠️ Aviso Importante

**Sempre fique atento ao que seu professor posta na plataforma SIGAA.**
Este material é complementar e composto por materiais coletados quando o monitor cursou as disciplinas. **Todo o conteúdo aqui disponível não substitui o material oficial e as instruções fornecidas pelos professores.**

---

## 🎯 Objetivos das Disciplinas

Ao final destas disciplinas, o aluno deve ser capaz de:

* Demonstrar o funcionamento dos periféricos: IO, Serial, PWM, ADC, Timers.
* Classificar as atividades em background e foreground.
* Implementar códigos em tempo real usando interrupção.
* Implementar códigos para interfaces de HW.
* Organizar o programa selecionando a melhor arquitetura de software.

---
## 🔗 Links Úteis

* **MPLab IDE:** [https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)
* **Compilador XC8:** [https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers/xc8](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers/xc8)
* **PICSimLab:** [https://github.com/lcgamboa/picsimlab](https://github.com/lcgamboa/picsimlab)

* **ECOP04/14 MAX:** [https://sites.google.com/unifei.edu.br/rodrigoalmeida/ecop04ecop14](https://sites.google.com/unifei.edu.br/rodrigoalmeida/ecop04ecop14)
---



## 📂 Estrutura desta Pasta
```
.
└── documentos/         # Provas resolvidas e material complementar
```

---

## 💡 Dicas do Monitor

1.  **LEIA O DATASHEET (e o Manual de Referência)!** A resposta para 90% das suas dúvidas sobre um periférico está lá. Aprenda a navegar no PDF do fabricante.
2.  **Domine Operações Bitwise:** Programação embarcada é, em essência, ler e escrever em registradores. Você *precisa* ser fluente em `|` (setar bit), `&` (checar/limpar bit), `~` (inverter) e `<<` / `>>` (deslocar bits).
3.  **Entenda Interrupções:** Este é o "pulo do gato" da programação embarcada. Entender o fluxo de uma interrupção é o que permite criar sistemas responsivos (tempo real) sem um Sistema Operacional.
4.  **Use o Debugger:** Não programe usando `printf`! Aprenda a usar o debugger para colocar *breakpoints*, inspecionar a memória e, o mais importante, **monitorar os registradores dos periféricos** em tempo real.

**Bons estudos!**