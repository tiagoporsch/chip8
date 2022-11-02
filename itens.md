# Classes, atributos e métodos
Absolutamente tudo foi implementado utilizando esses conceitos. Não sei como explicitar qual linha em qual arquivo pois seriam praticamente todas em todos.

# Encapsulamento respeitado
O acesso de membros por outras classes foi requisitado principalmente para acessar a `m_v` da classe `Registers`, e afins nas classes `Keyboard`, `Screen`; e foi feito utilizando uma função que retorna uma referência, após ser validado o indice do elemento que era necessário acessar.
- `include/chip8/registers.h`, linha 19

Quando esse nível todo de acesso não era necessário, há funções que escondem o funcionamento interno da classe, como a `pop()` e `push(uint16_t)` da classe `Stack`
- `include/chip8/stack.h`, linhas 18 e 19

# Uso de associação
A classe `CPU`, no arquivo `include/chip8/cpu.h` é a principal classe que une todos os componentes do CHIP8.
Visando uma implementação na vida real, a classe `Emulator` cria vários objetos (unidade de memória, display, teclado, etc), e "conecta" todos eles à CPU os passando como referência. Ou seja, a CPU tem acesso à todas as unidades, mas elas não sabem uma da outra.
- `include/chip8/emulator.h`, linhas 15 à 22
- `include/chip8/cpu.h`, linhas 17 à 23

# Alocação dinâmica
Nadinha, pois não é necessário. Assim como uma possível implementação em hardware de um CHIP8 não pode simplesmente criar mais memória RAM como desejar, eu não aloquei nada além do que é pré-definido.

# Sobrecarga de operação
Utilizei uma sobrecarga do operador de extração, para carregar a ROM na memória do emulador.
- `source/chip8/memory.cpp`, linhas 15 à 22

# Herança
O conceito de herança foi utilizado para implementar a classe `SfmlEmulator`, que herda da classe `Emulator`, e propõe uma front-end para os membros.
- `include/chip8/emulator.h` e `source/chip8/emulator.cpp`
- `include/gui/sfml.h` e `source/gui/sfml.cpp`

# C++17
Nada de ponteiros, apenas ponteiros inteligentes (se eu tivesse usado alocação dinâmica, é claro...)

Nada de `[]`, apenas `std::array`s
- `include/chip8/keyboard.h`, linha 12
- `include/chip8/memory.h`, linha 35

Nada de `memset` e `memcpy`, apenas métodos como `std::fill` e `std::copy`
- `source/chip8/keyboard.cpp`, linha 8
- `source/chip8/memory.cpp`, linhas 6 e 7

Usei alguns `for`s da maneira antiga, mas apenas pois era necessário iterar em um intervalo de inteiros, fora isso foram usados range-based `for` statements.
- `source/chip8/screen.cpp`, linhas 10 à 12

Declarando métodos tipados como `auto` e usando trailing return types
- Todas as declarações de métodos

Nada de `rand()`, utilizei os métodos mais novos do C++ para gerar números aleatórios
- `include/chip8/cpu.h`, linhas 25 e 26
- `source/chip8/cpu.cpp`, linha 120

Nada de casts antigos, apenas `static_cast`
- `source/chip8/cpu.cpp`, linhas 15 à 18

# Deve executar em Linux
Quem que usa Windows? Tudo aqui foi feito no Linux pro Linux :)

# Polimorfismo
A implementação de diferentes GUIs se baseia no polimorfismo. A classe `Emulator` pode tomar várias formas, apresentada nesse projeto temos a forma `SfmlEmulator`. Para criar uma noma implementação, basta herdar a classe `Emulator` e implementar os métodos necessários.
- `include/chip8/emulator.h` e `source/chip8/emulator.cpp`
- `include/gui/sfml.h` e `source/gui/sfml.cpp`

# Padrões de projeto
- Todos os include guards foram feitos utilizando o padrão de C++ da Google.
- Todos os membros de classe foram declarados com o prefixo `m_`
- Nomes de classe seguem PascalCase, nomes de membros seguem snake_case
- Membros de classe seguem essa ordem: private static, public static, private, public; após os membros temos os métodos, que seguem a ordem private, public.