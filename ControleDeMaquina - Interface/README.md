# Controle de Máquina - Interface

Interface de controle do sistema embarcado. 

## Instalação 

Para realizar a instalação é necessário fazer algumas configurações iniciais para seu sistema poder compilar o programa.

Primeiro ter o compilador do C/C++ e as ferramentas make e cmake, e o git para fazer o download dos arquivos contidos no repositório:

Instalação no Linux baseado em Debian:
```
sudo apt install gcc g++ make cmake git
```
Para Windows use o MinGw

Após instalar o compilador e ferramentas utilitárias, é necessário instalar o SDK do Qt.
Para isso acesse o site da [Documentação do Qt](https://doc.qt.io/qt-5/) e siga os passos para instalar.
Também, instale o QSerialPort, siga as instruções de instalação no site.

Após fazer todas essas configurações iniciais, primeiro faça o clone do repositório:
```
git clone https://github.com/lucasfturos/TCC-Controle-de-Maquina.git ; cd TCC-Controle-de-Maquina/ControleDeMaquina\ -\ Interface/
```

Com isso, após o download ser concluído ele já irá entrar na pasta da interface. Para gerar o executável é necessário fazer o seguinte:
```
mkdir build ; cd build
cmake ..
make
```

Após isso, se não ocorreu nenhum erro, é só executar o programa:
```
./ControleDeMaquina
```

## Referências 

Repositórios que usei como base para construir a comunicação serial do programa. 

```
https://github.com/qt/qtserialport
https://github.com/KROIA/QT-Serial-Communication-example
```
