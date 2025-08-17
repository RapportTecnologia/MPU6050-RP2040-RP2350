
## Autores e Colaboradores

- Carlos Delfino — consultoria@carlosdelfino.eti.br — GitHub: [@carlosdelfino](https://github.com/carlosdelfino)

# MPU6050-RP2040-RP2350

## Como obter este módulo (via workspace principal)

Para garantir que as dependências compartilhadas (ex.: `../I2C`, mocks, etc.) sejam resolvidas automaticamente, clone o repositório raiz (monorepo) com submódulos:

```bash
git clone --recurse-submodules https://github.com/RapportTecnologia/Sensores_e_Atuadores_do_Kit_BitDogLab.git Sensores_e_Atuadores_do_KIT
cd Sensores_e_Atuadores_do_KIT
git submodule update --init --recursive
```

Atualizar submódulos (quando aplicável):

```bash
git submodule update --remote --merge --recursive
```

Projeto de exemplo e driver do sensor inercial MPU6050 (acelerômetro + giroscópio) para a plataforma Raspberry Pi Pico (RP2040/RP2350), utilizando um proxy I2C simples (estilo Arduino Wire) para abstrair o acesso ao hardware.

## Sobre o sensor MPU6050
- **Fabricante**: InvenSense (TDK)
- **Funções**: Acelerômetro de 3 eixos e giroscópio de 3 eixos.
- **Interface**: I2C (endereço padrão 0x68 quando AD0 = GND).
- **Temperatura interna**: leitura disponível via registradores.

Neste projeto o dispositivo é inicializado com configuração padrão (±2g para acelerômetro e ±500 °/s para giroscópio) e realiza leituras periódicas, imprimindo os valores pela USB-CDC.

## Estrutura do projeto
```
MPU6050-RP2040-RP2350/
├─ CMakeLists.txt                 # Build com Pico SDK
├─ Doxyfile                       # Configuração Doxygen
├─ main.cpp                       # Exemplo de uso (aplicação)
├─ MPU6050/                       # Driver do sensor
│  ├─ MPU6050.h                   # Header com API e documentação
│  └─ MPU6050.cpp                 # Implementação do driver
└─ ../I2C/                        # Proxy I2C genérico (I2C.h / I2C.cpp)
```

## Pré-requisitos
- [Pico SDK](https://github.com/raspberrypi/pico-sdk) instalado e configurado.
- CMake 3.13+ e toolchain compatível (arm-none-eabi-gcc sugerido).
- Doxygen (opcional, apenas para gerar documentação).

## Como compilar e gravar
1. Inicialize submódulos e garanta o Pico SDK configurado no ambiente.
2. A partir da pasta `MPU6050-RP2040-RP2350/`:
   ```bash
   mkdir -p build
   cmake -B build -S .
   cmake --build build -j
   ```
3. O arquivo `.uf2` será gerado em `build/`. Coloque o Pico em modo bootloader e arraste o `.uf2` para a unidade USB montada.

## Uso do exemplo
- Conexões padrão utilizadas no exemplo (`main.cpp`):
  - I2C: `i2c0`, SDA no GPIO 1, SCL no GPIO 0
  - Clock I2C: 400 kHz
- Fluxo:
  - Inicializa USB-CDC e I2C
  - Instancia `MPU6050`, chama `begin()`
  - Em loop: lê aceleração, giroscópio e temperatura a cada 2 s e imprime

Saída típica no terminal serial:
```
I2C @ 400000 Hz
ID do Sensor: 68
Aceleracao X:0.02 Y:-0.01 Z:0.99
Giroscópio X:0.10 Y:-0.05 Z:0.03
Temperatura: 26.45
```

## API do driver (`MPU6050/MPU6050.h`)
Principais métodos:
- `begin()` – inicializa o dispositivo.
- `getId()` – retorna WHO_AM_I.
- `getAccelleration(VECT_3D* vect, float scale=16384.0)` – lê aceleração (g).
- `getGyroscope(VECT_3D* vect, float scale=65.5)` – lê giroscópio (°/s).
- `getTemp()` – lê temperatura (°C).

O driver utiliza um proxy `I2C` simples com API semelhante ao `Wire` (Arduino): `beginTransmission()`, `write()`, `requestFrom()`, `read()`, `endTransmission()`, etc. O código do proxy encontra-se em `../I2C/` e é incluído no build via `CMakeLists.txt`.

## Gerar documentação (Doxygen)
Na pasta `MPU6050-RP2040-RP2350/` execute:
```bash
doxygen Doxyfile
```
A documentação HTML é gerada em `docs/html/index.html`.

## Documentação

Este módulo possui instruções de geração de documentação via Doxygen (ver seção acima). Alternativamente, no monorepo você pode gerar a documentação consolidada a partir do `Doxyfile` da raiz.

## Licença
Este diretório inclui um arquivo `LICENSE` (CC0 1.0) com os termos. Veja também o arquivo `LICENSE` na raiz do repositório.

## Créditos
- Baseado no Pico SDK da Raspberry Pi e exemplos da comunidade.
- Estrutura do proxy I2C inspirada na API `Wire` (Arduino) para facilitar portabilidade.
