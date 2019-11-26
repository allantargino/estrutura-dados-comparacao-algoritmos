#ifndef RANDOMCL_H_INCLUDED
#define RANDOMCL_H_INCLUDED

template<typename Tipo> // Classe Template parao gerador
class RandomCL{
private:
	Tipo r; // Atributo para gera��o da sequ�ncia
	unsigned char i;

public:
	RandomCL(unsigned char i) { // Construtor
		this->i = i;
		reset();
	}

	Tipo nextr() { // M�todo da congru�ncia linear: a=17, b=23
		r = 17 * r + 23;
		return(r);
	}

	void reset() { // Inicia a sequencia com a semente
		unsigned short seeds[6] = { 4, 81, 151, 1601, 2307, 4207 };
		r = seeds[i % 6];
	}
};

#endif RANDOMCL_H_INCLUDED
