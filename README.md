Sistema de Monitoramento de Nível de Água com Arduino

Descrição

Este projeto apresenta um sistema embarcado para monitoramento do nível de água em um reservatório utilizando Arduino. O sistema lê sensores de nível simulados e mostra as informações em um display LCD.

O consumo de água também é monitorado através de um sensor de vazão simulado por um potenciômetro.

Como não há disponibilidade de um relé ou bomba real, o funcionamento do sistema de enchimento do reservatório é representado por um LED indicador.

Funcionamento do Sistema

O sistema mede o nível da água através de cinco sensores simulados por chaves liga/desliga.

Dependendo da altura detectada:

Se o nível estiver baixo, o sistema liga um LED indicando que o reservatório está sendo preenchido.

Quando o nível máximo é atingido, o LED é desligado indicando que o reservatório está cheio.

As informações de nível e consumo são exibidas em um display LCD 16x2.

O consumo total de água é armazenado na memória EEPROM do Arduino para evitar perda de dados caso o sistema seja desligado.

Níveis do Reservatório

Sensor 1 – 2 cm
Sensor 2 – 4 cm
Sensor 3 – 6 cm
Sensor 4 – 8 cm
Sensor 5 – 9 cm

Lógica de Funcionamento

Altura menor ou igual a 4 cm
Reservatório baixo – LED ligado indicando enchimento.

Altura entre 6 cm e 8 cm
Sistema apenas monitora o nível.

Altura maior ou igual a 9 cm
Reservatório cheio – LED desligado.

Componentes Utilizados

Arduino Uno
Display LCD 16x2
2 potenciômetros de 10kΩ
5 botões ou chaves liga/desliga
resistores de 10kΩ
1 LED
1 resistor de 220Ω
protoboard
cabos jumper

Estrutura do Código

O código foi dividido em funções para facilitar a organização:

lerNivel() – realiza a leitura dos sensores de nível.

controlarSistema() – controla o LED que representa o sistema de enchimento.

calcularConsumo() – calcula o consumo de água.

mostrarLCD() – exibe as informações no display.

Exemplo de saída no display

Nivel: 6cm
Cons: 120L

Simulação

O projeto pode ser testado utilizando o simulador Tinkercad antes da montagem física do circuito.

Objetivo

O objetivo deste projeto é demonstrar conceitos de sistemas embarcados aplicados ao monitoramento de recursos hídricos, utilizando sensores simulados, interface com display e armazenamento de dados em memória não volátil.
