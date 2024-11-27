#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>
#include "loja.h"

using namespace std;

/// Funcoes de entrada/saida
void Produto::digitar()
{
  // Leh o nome do produto
  do
  {
    cout << "Nome: ";
    getline(cin,nome);
  }
  while (nome=="");
  // Leh o preco do produto
  do
  {
    cout << "Preco (##.##): ";
    cin >> preco;
  }
  while (preco <= 0.0);
  cin.ignore();
}

/// Define a funcao imprimir como sendo salvar em cout
void Produto::imprimir() const
{
  salvar(cout);
}

bool Produto::ler(istream& I)
{
  // Formato da linha no arquivo-> "STRING_NOME";$FLOAT_PRECO
  try
  {
    // Ignora ateh aspa inicial
    I.ignore(numeric_limits<streamsize>::max(),'"');
    // Leh ateh a aspa final do nome do produto
    getline(I,nome,'"');
    if (!I.good() || nome=="") throw 1;
    // Ignora o ";" e o "$"
    I.ignore(numeric_limits<streamsize>::max(),'$');
    // Leh o preco como numero real
    I >> preco;
    if (!I.good() || preco<=0.0) throw 2;
  }
  catch (int i)
  {
    // Erro na leitura
    nome = "";
    preco = 0;
    return false;
  }
  return true;
}

void Produto::salvar(ostream& O) const
{
  // Formato da linha-> "STRING_NOME";$FLOAT_PRECO;
  O << '"' << nome << '"' << ";$" << fixed << setprecision(2) << preco;
}

istream& operator>>(istream& I, Produto& P)
{
  P.digitar();
  return I;
}

ostream& operator<<(ostream& O, const Produto& P)
{
  P.salvar(O);
  return O;
}

/// CLASSE LIVRO

/// IMPLEMENTE A CLASSE LIVRO

istream& operator>>(istream& I, Livro& L)
{
  L.digitar();
  return I;
}

ostream& operator<<(ostream& O, const Livro& L)
{
  L.salvar(O);
  return O;
}

/// CLASSE CD

/// IMPLEMENTE A CLASSE CD

istream& operator>>(istream& I, CD& C)
{
  C.digitar();
  return I;
}

ostream& operator<<(ostream& O, const CD& C)
{
  C.salvar(O);
  return O;
}

/// CLASSE DVD

/// IMPLEMENTE A CLASSE DVD

istream& operator>>(istream& I, DVD& D)
{
  D.digitar();
  return I;
}

ostream& operator<<(ostream& O, const DVD& D)
{
  D.salvar(O);
  return O;
}

/// CLASSE LOJA

/// Funcoes de consulta

Livro Loja::getLivro(int id) const
{
  if (LL.empty() || id<0 || id>=(int)LL.size()) return Livro();
  return LL[id];
}

CD Loja::getCD(int id) const
{
  if (LC.empty() || id<0 || id>=(int)LC.size()) return CD();
  return LC[id];
}

DVD Loja::getDVD(int id) const
{
  if (LD.empty() || id<0 || id>=(int)LD.size()) return DVD();
  return LD[id];
}

/// Funcoes de manipulacao (inclusao/exclusao) de itens do estoque

bool Loja::excluirLivro(int id)
{
  if (LL.empty() || id<0 || id>=(int)LL.size()) return false;
  LL.erase(LL.begin()+id);
  return true;
}

bool Loja::excluirCD(int id)
{
  if (LC.empty() || id<0 || id>=(int)LC.size()) return false;
  LC.erase(LC.begin()+id);
  return true;
}

bool Loja::excluirDVD(int id)
{
  if (LD.empty() || id<0 || id>=(int)LD.size()) return false;
  LD.erase(LD.begin()+id);
  return true;
}

/// Funcoes de entrada/saida

void Loja::imprimir() const
{
  cout << ">> LIVROS:" << endl;
  for (int i=0; i<(int)LL.size(); i++) cout << i << ") " << LL[i] << endl;

  cout << ">> CDS:" << endl;
  for (int i=0; i<(int)LC.size(); i++) cout << i << ") " << LC[i] << endl;

  cout << ">> DVDS:" << endl;
  for (int i=0; i<(int)LD.size(); i++) cout << i << ") " << LD[i] << endl;
}

bool Loja::ler(const string& arq)
{
  // A stream de leitura
  ifstream I(arq.c_str());

  // O resultado logico da leitura
  bool resultado=true;

  try
  {
    if (!I.is_open()) throw 1;

    string pS;
    int NN;
    Livro L;
    CD C;
    DVD D;

    // Leh os livros
    I >> pS >> NN;
    if (I.fail() || pS!="LISTALIVRO") throw 2;
    I >> ws;
    LL.clear();
    for (int i=0; i<NN; i++)
    {
      if (!L.ler(I)) throw 3;
      LL.push_back(L);
    }

    // Leh os CDs
    I >> pS >> NN;
    if (I.fail() || pS!="LISTACD") throw 4;
    I.ignore();
    LC.clear();
    for (int i=0; i<NN; i++)
    {
      if (!C.ler(I)) throw 5;
      LC.push_back(C);
    }

    // Leh os DVDs
    I >> pS >> NN;
    if (I.fail() || pS!="LISTADVD") throw 6;
    I.ignore();
    LD.clear();
    for (int i=0; i<NN; i++)
    {
      if (!D.ler(I)) throw 7;
      LD.push_back(D);
    }
  }
  catch (int i)
  {
    LL.clear();
    LC.clear();
    LD.clear();
    resultado = false;
  }
  return resultado;
}

bool Loja::salvar(const string& arq) const
{
  ofstream O(arq.c_str());
  if (!O.is_open()) return false;

  O << "LISTALIVRO " << LL.size() << endl;
  for (int i=0; i<(int)LL.size(); i++) O << LL[i] << endl;

  O << "LISTACD " << LC.size() << endl;
  for (int i=0; i<(int)LC.size(); i++) O << LC[i] << endl;

  O << "LISTADVD " << LD.size() << endl;
  for (int i=0; i<(int)LD.size(); i++) O << LD[i] << endl;

  return true;
}
