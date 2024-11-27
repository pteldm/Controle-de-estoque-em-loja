#ifndef _LOJA_H_
#define _LOJA_H_

#include <iostream>
#include <string>
#include <vector>

class Produto
{
private:
  std::string nome;
  double preco;
public:
  /// Construtor default
  Produto(const std::string& N, double P): nome(N), preco(P) {}

  /// Funcoes de consulta
  const std::string& getNome() const
  {
    return nome;
  }
  double getPreco() const
  {
    return preco;
  }

  /// Metodos de entrada/saida
  void digitar();
  void imprimir() const;

  bool ler(std::istream& I);
  void salvar(std::ostream& O) const;
};

std::istream& operator>>(std::istream& I, Produto& P);
std::ostream& operator<<(std::ostream& O, const Produto& P);

/// DECLARE A CLASSE LIVRO

std::istream& operator>>(std::istream& I, Livro& L);
std::ostream& operator<<(std::ostream& O, const Livro& L);

/// DECLARE A CLASSE CD

std::istream& operator>>(std::istream& I, CD& C);
std::ostream& operator<<(std::ostream& O, const CD& C);

/// DECLARE A CLASSE DVD

std::istream& operator>>(std::istream& I, DVD& D);
std::ostream& operator<<(std::ostream& O, const DVD& D);

class Loja
{
private:
  std::vector<Livro> LL;
  std::vector<CD>    LC;
  std::vector<DVD>   LD;
public:
  /// Construtor
  Loja(): LL(), LC(), LD() {}

  /// Funcoes de consulta
  int getNumLivro() const
  {
    return LL.size();
  }

  int getNumCD() const
  {
    return LC.size();
  }

  int getNumDVD() const
  {
    return LD.size();
  }
  Livro getLivro(int id) const;
  CD getCD(int id) const;
  DVD getDVD(int id) const;

  /// Funcoes de manipulacao (inclusao/exclusao) de itens do estoque
  void incluirLivro(const Livro& X)
  {
    LL.push_back(X);
  }
  bool excluirLivro(int id);
  void incluirCD(const CD& X)
  {
    LC.push_back(X);
  }
  bool excluirCD(int id);
  void incluirDVD(const DVD& X)
  {
    LD.push_back(X);
  }
  bool excluirDVD(int id);

  /// Funcoes de entrada/saida
  bool ler(const std::string& arq);
  bool salvar(const std::string& arq) const;
  void imprimir() const;
};
#endif // _LOJA_H_
