#include <iostream>
#include <set>

struct Persona {
  std::string nome;
  int eta;

  Persona(std::string newNome, int newEta) {
    nome = newNome;
    eta = newEta;
  }

  bool operator<(const Persona& seconda) const {
    if (eta == seconda.eta) {
      return nome < seconda.nome;
    } else {
      return eta < seconda.eta;
    }
  }
};

int main() {
  std::set<double> settete;

  settete.insert(5.3);
  settete.insert(2.8);
  settete.insert(8.5);
  settete.insert(1.7);

  std::cout << "set:";
  for (auto& bubu : settete) {
    std::cout << " " << bubu;
  }
  std::cout << std::endl;

  


  std::set<Persona> persone;
  
  persone.insert(Persona(std::string("Aldo"), 30));
  persone.insert(Persona(std::string("Carlo"), 5));
  persone.insert(Persona(std::string("Bob"), 5));

  std::cout << "pers:";
  for (auto& currPers : persone) {
    std::cout << " " << currPers.nome;
  }
  std::cout << std::endl;



  return 0;
}

