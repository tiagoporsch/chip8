#include <exemplo/exemplo.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <random>

/*
 Projeto para execução em terminal.
 
 Configurado para utilizar C++17.
 Portanto, sugere-se um compilador que suporte essa versão.
 
 */

void teste_compilador() {
    static_assert(__cplusplus >= 201703L, "Projeto requer compilador compatível com C++17.");
}

auto numero_aleatorio() {
    std::uniform_int_distribution<int> randomDist(0, 50);
    std::random_device rd;
    std::mt19937 randomNumbers(rd());
    return randomDist(randomNumbers);
}


auto main(int argc, char** argv) -> int {
  const std::unordered_map<std::string, greeter::LanguageCode> languages{
      {"en", greeter::LanguageCode::EN},
      {"de", greeter::LanguageCode::DE},
      {"es", greeter::LanguageCode::ES},
      {"fr", greeter::LanguageCode::FR},
  };
  std::cout << "Projeto Terminal: " << numero_aleatorio() << '\n';

  std::string language{"en"};
  std::string name{"aluno de EMB5631"};

  auto langIt = languages.find(language);
  if (langIt == languages.end()) {
    std::cerr << "unknown language code: " << language << std::endl;
    return 1;
  }

  greeter::Greeter greeter(name);
  std::cout << greeter.greet(langIt->second) << std::endl;

  return 0;
}
