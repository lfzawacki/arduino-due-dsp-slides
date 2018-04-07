% Processamento de Áudio com Arduino Due
% Lucas Fialho Zawacki

Jabá Matehackers
=

\centerline{\includegraphics[height=1.5in]{assets/images/logo.png}}
![](assets/images/logo.png)

## **Hackers + Espaço = Hackerspace**

<http://matehackers.org>

Quem sou?
=

![](assets/images/lucas.jpeg)

* Lucas Fialho Zawacki
* Ciêntista da Computação, [Matehackers](https://matehackers.org), [Mconf](https://mconf.com)
* [Musical Aritfacts](https://musical-artifacts.com), [Ownlife Project](https://ownlife.lfzawacki.com/)

O que queremos fazer aqui?
=

* Usar um Arduino Due como processador de sinais digitais
* Aprender como funciona áudio e áudio digital
* Fazer os nossos próprios efeitos de áudio baseados no som de uma guitarra

O que queremos fazer aqui? (cont.)
=

![Zoomzera](assets/images/zoom.jpg)

Processamento de Sinais Digitais (DSP)
=

1. Fonte sonora
1. Onda elétrica
1. Conversão Analógico-Digital (ADC)
1. **Código (manipulação digital dos dados)**
1. Conversão Digital-Analógica (DAC)
1. Saída de Som (caixas de som, fones-de-ouvido)

Diagrama DSP
=

![Fonte: [Wikipedia - Digital Audio](https://en.wikipedia.org/wiki/Digital_audio)](assets/images/dsp.png)

Como funcionam ondas sonoras
=

* Váriação de pressão do ar
* Frequência da variação -> "Nota"
* Amplitude -> "Volume"
* Podemos converter ondas sonoras (mecânicas) em ondas eletricas

Ondas Sonoras
=

![Seno](assets/images/seno.png)

![Onda bateria](assets/images/bateria.png)

Áudio Digital
=

* Representação numérica de uma frequência elétrica
* É feita como uma amostragem de partes da onda original...
* Virando uma sequência de números no tempo

![Amostragem](assets/images/amostragem.png)



Taxa de Amostragem
=

Qual a influência da taxa de amostragem?

![](assets/images/taxas-amostragem.png)

<div>
11025 KHz
<audio data-src="assets/sounds/amenbreak-less.ogg" type="audio/ogg" controls="controls"></audio>

</div>

<div>
44100 KHz
<audio data-src="assets/sounds/amenbreak.ogg" type="audio/ogg" controls="controls"></audio>
</div>

Diferentes Ondas
=

* Seno, Triângulo, Quadrada, Dente de Serra, Pulso, ...
* ... o resto!

![](assets/images/ondas1.png)
<br>
![](assets/images/ondas2.png)

Arduino Due
=

* Arduino Baseado no Atmel SAM3X8E ARM Cortex-M3 CPU
* 32 bits, mais memória, mais processador
* Muito mais inputs e outputs
* DACs e ADCs

Pinagem Arduino Due
=

[![](assets/images/due-pins.png)](assets/images/due-pins.png)

Demonstração do DAC
=

* <https://gist.github.com/pklaus/5921022>

Projeto inspirador
=

<iframe width="860" height="560" src="https://www.youtube.com/embed/COPaqJBekBQ" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

Circuito
=

![](assets/images/circuito.jpg)

* Um amplificador baseado no Fetzer Valve com MPF102
* <http://www.runoffgroove.com/fetzervalve.html>

Voltagem e PCM
=

* Amplificação e amostragem do sinal de guitarra
* Valores variando entre 900 e 1400
* Um pouco de ruído
* Porém temos o nosso som!

Código
=

![](assets/images/code.jpg)

Demos
=

* Guitarra limpa
* Distorção
* Córus + Distorção

Dúvidas
=

![](assets/images/duvidas.jpg)

Muito Obrigado
=

:)