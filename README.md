
# Projeto Saude Unica

# Problematica

A falta de integração entre os serviços de saúde resulta em dificuldades na escolha de onde buscar atendimento, devido à falta de visibilidade sobre a disponibilidade de profissionais. Isso gera longos tempos de espera e afeta negativamente a experiência do usuário. Além disso, a ausência de um acompanhamento integrado compromete a construção de uma história clínica completa para os pacientes, perdendo noção do tempo total necessário para conclusão de sua "jornada" médica. A falta de continuidade nas consultas e tratamentos dificulta a gestão eficaz dos cuidados de saúde.
Um dos fatores que implica na ausência de profissionais por local de saúde é a disponibilidade de insumos para serem utilizados. Por vezes, a falta de controle preciso dos insumos essenciais, como umidade e temperatura, influencia a disponibilidade desses recursos nos estabelecimentos de saúde, podendo resultar em interrupções ou atrasos nos tratamentos.

# Solução

Centralizando o acesso e permitindo a escolha entre locais de atendimento, públicos ou privados, por meio de uma plataforma unificada, o Saúde Única simplifica o agendamento via web ou aplicativo, evitando a busca por locais com escassez de profissionais. Além disso, a integração proposta também inclui o monitoramento em tempo real dos insumos médicos nos estabelecimentos de saúde, exibindo dados como umidade e temperatura em um dashboard na plataforma. Essa abordagem visa garantir o abastecimento adequado de recursos, evitando interrupções nos atendimentos. A combinação desses elementos busca aprimorar a experiência do usuário, oferecendo maior eficiência nos cuidados de saúde e promovendo um acompanhamento contínuo da saúde do paciente.

# Montagem
Para a montagem do projeto de monitoramento será necessário utilizar:
- Plataforma Wokwi (para reproduzir a simulação);
- Programa Arduino IDE (juntamente com o código);
- Kit básico de componentes físicos do Arduino, detalhados abaixo:
<table>
  <tr>
    <td><b>Componente</b></td>
    <td align=center><b>Quantidade</b></td>
  </tr>
    <tr>
    <td>Placa ESP32</td>
    <td align=center>1</td>
  </tr>
  <tr>
    <td>Buzina "piezo"</td>
    <td align=center>1</td>
  </tr>
    <tr>
    <td>Resistor 10kΩ</td>
    <td align=center>1</td>
  </tr>
  <tr>
    <td>Sensor DHT22</td>
    <td align=center>1</td>
  </tr>
</table>

Basta agora reproduzir o modelo do Wokwi utilizando os combonentes físicos listados. Para execução, é necessário conectar a placa ESP32 a um computador via micro-USB, inserir o código de execução no programa Arduino IDE e fazer o upload.

# Parâmetros

temperatura ideal: entre 15 a 30ºC 
umidade ideal: 40 e 70%
___
### Pré-requisitos
Para execução do projeto é necessário conhecimento sobre o uso da plataforma Wokwi, e experiência com o uso do programa Arduino e de seus componentes físicos. É necessário também saber usos básicos da linguagem C++ para entendimento do código e ajustes necesários.
___

### Links

[Link para o projeto no Wokwi](https://wokwi.com/projects/381961116500578305)
