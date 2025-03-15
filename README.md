# Carregador Inteligente para Baterias 18650

O objetivo desse projeto é desenvolver um carregador inteligente para até quatro baterias 18650, com controle de carga independente e interação com o usuário por meio de uma interface web.

## Especificações Gerais

- O carregador deve ser capaz de carregar até quatro baterias 18650 simultaneamente.
- Cada bateria será carregada de forma independente.
- O carregador deve suportar correntes de carga de até 2,5A por bateria.
- O usuário poderá visualizar e interagir com as informações por meio de uma interface web acessível através da rede local.
- A interface web deverá permitir alterar o valor da corrente de carregamento e ser capaz de monitorar em tempo real dos seguintes parâmetros (individualmente para cada célula): tensão, temperatura, porcentagem de carga, tempo decorrido e previsão de tempo restante.
- O carregador deve incluir as seguintes proteções: sobrecorrente, sobreaquecimento, polarização invertida e desligamento automático caso a temperatura ultrapasse um valor seguro.
- O carregador será alimentado através de uma fonte com saída USB-C com PD negociado a 20V.
- O carregador deve ter uma eficiência mínima de 80% para minimizar perdas térmicas.

## Hardware Principal

- Microcontrolador ESP32
- 4 circuitos integrados de gerenciamento de carga (inicialmente o CI BQ25703A será escolhido), comunicando-se via I²C com o microcontrolador (um para cada bateria).
- Display IPS 240x320.
