# # how-to Arduino

### Utilizando o ATMEGA328 com 4 Displays LED de 7 segmentos para criar um contador auto reiniciável de uma hora. <p>

* Utilização de registradores
* Baixa memória
* Baseado em incrementação com delay
* Botões de Controle
#
## Update 1.1

### Foi adicionado um sistema de interrupções externas, conhecidas por `INT0` e `INT1`, elas foram configuradas neste projeto como "botões já pré definidos" (PD2/2 e PD3/3) e realizam funções no contador ao serem pressionados.
<br>

### A primeira interrupção `INT0` funciona como um "play/pause". Ao ser pressionada ela realiza o início da contagem e, ao pressionar novamente, ela pausa o ciclo e continua printando o que já foi contado.
<br>

### A segunda interrupção `INT1` funciona como um "reset". Ao ser pressionada ela reinicia todas as variáveis do código e, devido a isso o contador volta ao seu estado inicial.
#

### Para o sucesso desta atualização, ocorreu uma mudança massiva no código implementando novas funções e lógicas de programação, como: <p>

* Matriz de Arrays
* Configuração de Interrupções
* Funções de execuções específicas
* Lógica XOR
#

<p align="center">
  <img src="./images/counter.png" alt="print do PinSimLab"/><br>
  Print do contador no PICSimLab
</p>