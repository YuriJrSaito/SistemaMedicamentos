#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<windows.h>

struct LDDEPessoas{
	char sexo;
	char pais[50], medicamento[200];
	char codigoPessoa[12];
	char ultimaCompra[11];
	LDDEPessoas *ant, *prox;
};

struct LDSEMedicamentos{
	char medicamento[200];
	LDDEPessoas *Pessoas;
	LDSEMedicamentos *prox;
};

struct LDDEPaises{
	char pais[50];
	LDSEMedicamentos *Medicamentos;
	LDDEPaises *ant, *prox;
};

struct TpDescritorPaises{
   LDDEPaises *Inicio, *Final;
   int Qtde;
};

void InicializarDescritor(TpDescritorPaises &Desc)
{
   Desc.Inicio = Desc.Final = NULL;
   Desc.Qtde = 0;
}

LDDEPaises *NovoPais(char pais[50])
{
    LDDEPaises *pCaixa = new LDDEPaises;
    strcpy(pCaixa->pais, pais);
    pCaixa->ant = NULL;
    pCaixa->prox = NULL;
    pCaixa->Medicamentos = NULL;	
    return pCaixa;
}

LDSEMedicamentos *NovoMedicamento(char medicamento[200]){
	LDSEMedicamentos *pCaixa = new LDSEMedicamentos;
	strcpy(pCaixa->medicamento, medicamento);
    pCaixa->prox = NULL;
    pCaixa->Pessoas = NULL;
    return pCaixa;
}

LDDEPessoas *NovaPessoa(char pais[50], char medicamento[200], char codigoPessoa[12], char ultimaCompra[11], char sexo){
	LDDEPessoas *pCaixa = new LDDEPessoas;
	pCaixa->sexo = toupper(sexo);
	pais[0] = toupper(pais[0]);
	strcpy(pCaixa->pais, pais);
	medicamento[0] = toupper(medicamento[0]);
	strcpy(pCaixa->medicamento, medicamento);
	strcpy(pCaixa->codigoPessoa, codigoPessoa);
	strcpy(pCaixa->ultimaCompra, ultimaCompra);
	pCaixa->prox = NULL;
	pCaixa->ant = NULL;
	return pCaixa;
}

LDDEPaises *buscaPais(TpDescritorPaises &lista, char pais[50]){
	LDDEPaises *p;
	if(lista.Inicio == NULL)
		return p = NULL;
	else{
		p = lista.Inicio;
		while(p != NULL && stricmp(p->pais,pais)!=0)
			p = p->prox;
	}
	return p;
}

LDSEMedicamentos *buscaMedicamento(char medicamento[200], LDDEPaises *paisAux){
	LDSEMedicamentos *auxMed;
	
	if(paisAux == NULL)
		return auxMed = NULL;
	else{
		auxMed = paisAux->Medicamentos;
		while(auxMed != NULL && stricmp(auxMed->medicamento, medicamento)!=0)
			auxMed = auxMed->prox;
	}
	return auxMed;
}

LDDEPessoas *buscaPessoa(char codigoPessoa[12], LDSEMedicamentos *medAux){
	LDDEPessoas *pAux;
	
	if(medAux->Pessoas == NULL)
		return pAux = NULL;
	else{
		pAux = medAux->Pessoas;
		while(pAux != NULL && stricmp(pAux->codigoPessoa, codigoPessoa)!=0)
			pAux = pAux->prox;
	}
	return pAux;
}

void exibeLista(TpDescritorPaises lista){
	LDSEMedicamentos *m;
	LDDEPessoas *p;
	
	while(lista.Inicio != NULL){
		m = lista.Inicio->Medicamentos;
				printf("\n======================\n");
		printf("Pais: %s\n", lista.Inicio->pais);
		while(m != NULL){
			p = m->Pessoas;
			printf("\tMedicamento: %s\n", m->medicamento);
			while(p != NULL){
				printf("\t\tPessoa: %s   ", p->codigoPessoa);
				printf("%s ", p->ultimaCompra);
				printf(" %c \n", p->sexo);
				p = p->prox;
			}
			m = m->prox;
		}
		lista.Inicio = lista.Inicio->prox;
	}
	getch();
}

LDDEPaises *inserePais(TpDescritorPaises &lista, char pais[50]){
	LDDEPaises *auxP, *NP = NovoPais(pais);
	
	auxP = buscaPais(lista, pais);
	if(auxP != NULL)
		return auxP;
	else{
		if(lista.Inicio == NULL){
			lista.Inicio = lista.Final = NP;
		}
		else{
			if(stricmp(pais, lista.Inicio->pais)<=0){
				NP->prox = lista.Inicio;
				lista.Inicio->ant = NP;
				lista.Inicio = NP;
			}
			else{
				if(stricmp(pais,lista.Final->pais)>=0){
					NP->ant = lista.Final;
					lista.Final->prox = NP;
					lista.Final = NP;
				}
				else{
					auxP = lista.Inicio->prox;
					while(stricmp(pais, auxP->pais)>0)
					auxP = auxP->prox;
					NP->prox = auxP;
					NP->ant = auxP->ant;
					auxP->ant = NP;
					NP->ant->prox = NP;
				}
			}
		}
		return NP;
	}
	lista.Qtde++;
}

LDSEMedicamentos *insereMedicamento(LDDEPaises *pAux, char medicamento[200]){
	LDSEMedicamentos *auxM, *NM = NovoMedicamento(medicamento);
	
	auxM = buscaMedicamento(medicamento, pAux);
	if(auxM != NULL)
		return auxM;
	else{
		if(pAux->Medicamentos == NULL)
			pAux->Medicamentos = NM;				
		else{
			auxM = pAux->Medicamentos;
			NM->prox = auxM;
			pAux->Medicamentos = NM;
		}
		return pAux->Medicamentos;
	}		
}


void inserePessoa(TpDescritorPaises &lista, char codigoPessoa[12], char sexo, char medicamento[200], char ultimaCompra[11], char pais [50]){
	
	LDDEPessoas *pessoaAux, *pessoa;
	LDSEMedicamentos *medAux;
	LDDEPaises *paisAux;
	
	pessoa = NovaPessoa(pais,medicamento,codigoPessoa,ultimaCompra,sexo);
	
	if(pessoa != NULL){
		paisAux = inserePais(lista, pessoa->pais);
		if(stricmp(paisAux->pais,pessoa->pais)==0){
			medAux = insereMedicamento(paisAux,pessoa->medicamento);	
			if(stricmp(medAux->medicamento,pessoa->medicamento)==0){
				pessoaAux = buscaPessoa(pessoa->medicamento, medAux);
				if(medAux->Pessoas == NULL)
					medAux->Pessoas = pessoa;
				else{
					pessoaAux = medAux->Pessoas;
					pessoa->prox = pessoaAux;
					pessoaAux->ant = pessoa;
					medAux->Pessoas = pessoa;
				}
			}
		}
	}
}

void carregaLista(TpDescritorPaises &lista){	
	LDDEPessoas aux; 
	FILE *ptr = fopen("Medicamentos.txt","r");
	
	fscanf(ptr,"%[^;]; %c; %[^;]; %[^;]; %[^;];\n", &aux.codigoPessoa, &aux.sexo, &aux.medicamento, &aux.ultimaCompra, &aux.pais);
	while(!feof(ptr)){
		inserePessoa(lista, aux.codigoPessoa, aux.sexo, aux.medicamento, aux.ultimaCompra, aux.pais);
		fscanf(ptr,"%[^;]; %c; %[^;]; %[^;]; %[^;];\n", &aux.codigoPessoa, &aux.sexo, &aux.medicamento, &aux.ultimaCompra, &aux.pais);
	}
	inserePessoa(lista, aux.codigoPessoa, aux.sexo, aux.medicamento, aux.ultimaCompra, aux.pais);
	fclose(ptr);
}

void excluirPessoas(LDSEMedicamentos *aux){
	LDDEPessoas *pessoasAux;
	
	if(aux->Pessoas != NULL){
		while(aux->Pessoas != NULL){
			pessoasAux = aux->Pessoas;
			if(pessoasAux->prox == NULL){
				printf("\nPessoa excluida %s", pessoasAux->codigoPessoa);
				delete(pessoasAux);
				aux->Pessoas = NULL;
			}
			else{
				pessoasAux = aux->Pessoas;
				aux->Pessoas = pessoasAux->prox;
				pessoasAux->prox->ant = NULL;
				pessoasAux->prox = NULL;
				printf("\nPessoa excluida %s", pessoasAux->codigoPessoa);
				delete(pessoasAux);
			}
		}
	}
	else
		printf("\nNao ha pessoas neste medicamento");
}	
	

void excluirPais(TpDescritorPaises &lista, char pais[50]){
	LDDEPaises *aux, *anterior, *proximo;
	LDSEMedicamentos *mAux;
	LDDEPessoas *pAux;
	
	aux = buscaPais(lista,pais);
	if(aux == NULL)
		printf("\nPais nao encontrado");
	else{
		if(stricmp(aux->pais,pais)==0){
			while(aux->Medicamentos != NULL){
				mAux = aux->Medicamentos;	
				
				excluirPessoas(mAux);
				
				mAux = aux->Medicamentos;
				aux->Medicamentos = mAux->prox;
				mAux->prox = NULL;
				delete(mAux);
				printf("\nMedicamento excluido");	
			}
			if(stricmp(aux->pais,lista.Inicio->pais)==0){
				lista.Inicio = aux->prox;
				lista.Inicio->ant = NULL;
				aux->prox = NULL;
				delete(aux);
			}
			else{
				if(stricmp(aux->pais,lista.Final->pais)==0){
					lista.Final = aux->ant;
					aux->ant = NULL;
					lista.Final->prox = NULL;
					delete(aux);
				}
				else{
					proximo = aux->prox;
					anterior = aux->ant;
					anterior->prox = proximo;
					proximo->ant = anterior;
					aux->prox = NULL;
					aux->ant = NULL;
					delete(aux);
				}
			}
			printf("\nPais excluido");
		}
		else
			printf("\nPais nao encontrado");	
	}
	getch();
}

void excluirMedicamento(TpDescritorPaises &lista, char medicamento[200]){
	LDSEMedicamentos *aux, *ant;
	LDDEPaises *paisAux;
	LDDEPessoas *pessoasAux;
	
	if(lista.Inicio == NULL)
		printf("\nLista vazia!");
	else{
		paisAux = lista.Inicio;
		while(paisAux != NULL){
			if(paisAux->Medicamentos != NULL){
				aux = buscaMedicamento(medicamento, paisAux);
				if(aux != NULL){	
								
					excluirPessoas(aux);
					
					if(aux->medicamento == paisAux->Medicamentos->medicamento){
						paisAux->Medicamentos = aux->prox;
						aux->prox = NULL;
					}
					else{
						aux = paisAux->Medicamentos;
						while(aux->prox != NULL && stricmp(aux->medicamento, medicamento)!=0){
							ant = aux;
							aux = aux->prox;
						}
						if(stricmp(aux->medicamento, medicamento)==0){
							ant->prox = aux->prox;
							aux->prox = NULL;
						}
					}
					delete(aux);
					printf("\nMedicamento excluido");
				}
			}
			if(paisAux->Medicamentos == NULL)
				excluirPais(lista, paisAux->pais);
			paisAux = paisAux->prox;	
		}
	}
	getch();	
}

void exibirMedPais(TpDescritorPaises lista, char pais[50]){
	LDSEMedicamentos *mAux;
	int cont = 0;
	if(lista.Inicio == NULL)
		printf("\nLista Vazia!!");
	else{
		lista.Inicio = buscaPais(lista,pais);
		if(lista.Inicio != NULL){
			mAux = lista.Inicio->Medicamentos;
			printf("\nMedicamentos: ");
			while(mAux != NULL){
				printf("\n\t%s",mAux->medicamento);
				cont++;
				mAux = mAux->prox;
			}
		}
		else
			printf("\nPais nao encontrado");
	}
	if(cont == 0){
		printf("\nNao ha medicamentos neste pais, ele sera excluido");
		excluirPais(lista, pais);
	}
	getch();
}

void exibirMedUsuarios(TpDescritorPaises lista, char medicamento[200]){
	LDSEMedicamentos *mAux;
	LDDEPessoas *pAux;
	
	int cont = 0;
	printf("\nMedicamento: %s", medicamento);
	if(lista.Inicio == NULL)
		printf("\nLista vazia!");
	else{
		while(lista.Inicio != NULL){
			mAux = buscaMedicamento(medicamento, lista.Inicio);
			if(mAux != NULL){
				pAux = mAux->Pessoas;
				printf("\n\tPais: %s", lista.Inicio->pais);
				printf("\n\t\tUsuarios: ");
				while(pAux != NULL){
					printf("\n\t\t\tCodigo da pessoa: %s ", pAux->codigoPessoa);
					printf("  Sexo: %c: ", pAux->sexo);
					printf("  Ultima compra: %s\n", pAux->ultimaCompra);
					pAux = pAux->prox;
					cont++;
				}
			}
			lista.Inicio = lista.Inicio->prox;
		}
	}
	if(cont == 0)
		printf("\nNao ha usuarios para este medicamento");
	getch();
}

void relatorio(TpDescritorPaises lista){
	
	LDDEPaises *paisAux;
	LDSEMedicamentos *medAux;
	LDDEPessoas *pessoaAux;
	FILE *ptr = fopen("Relatorio.txt","w");
	
	if(lista.Inicio == NULL)
		printf("\nLista vazia!");
	else{
		paisAux = lista.Inicio;
		while(paisAux != NULL){
			medAux = paisAux->Medicamentos;
			fprintf(ptr,"%s\n", paisAux->pais);
			fprintf(ptr,"   Feminino\n");
			while(medAux != NULL){
				pessoaAux = medAux->Pessoas;
				while(pessoaAux != NULL){
					if(pessoaAux->sexo == 'F')
						fprintf(ptr,"      Codigo: %s  Ultima compra: %s  Medicamento: %s\n", pessoaAux->codigoPessoa, pessoaAux->ultimaCompra, pessoaAux->medicamento);
					pessoaAux = pessoaAux->prox;
				}
				medAux = medAux->prox;
			}
			fprintf(ptr,"\n");
			fprintf(ptr,"   Masculino\n");
			medAux = paisAux->Medicamentos;
			while(medAux != NULL){
				pessoaAux = medAux->Pessoas;
				while(pessoaAux != NULL){
					if(pessoaAux->sexo == 'M')
						fprintf(ptr,"      Codigo: %s  Ultima compra: %s  Medicamento: %s\n", pessoaAux->codigoPessoa, pessoaAux->ultimaCompra, pessoaAux->medicamento);
					pessoaAux = pessoaAux->prox;
				}
				medAux = medAux->prox;
			}
			fprintf(ptr,"\n\n");
			paisAux = paisAux->prox;
		}
	}
	printf("Relatorio gerado");
	getch();
	fclose(ptr);
}

int main(){
	char op;
	TpDescritorPaises lista;
	InicializarDescritor(lista);
	carregaLista(lista);
	
	LDDEPessoas pAux;
		
	do
	{
		system("cls");
		printf("[I] Inserir um novo usuario: \n");
		printf("[E] Exibir lista: \n");
		printf("[M] Excluir um pais\n");
		printf("[V] Excluir medicamento\n");
		printf("[A] Exibir todos medicamentos de um determinado pais\n");
		printf("[B] Exibir todos usuarios a partir de um medicamento\n");
		printf("[N] Relatorio\n");
		
		op=toupper(getch());
		fflush(stdin);
		switch(op)
		{	
			case 'I':system("cls");
					 printf("\nPais: "); fflush(stdin);
					 gets(pAux.pais);
					 printf("\nMedicameto: ");fflush(stdin);
					 gets(pAux.medicamento);
					 printf("\nSexo (M/F): ");
					 scanf("%c", &pAux.sexo);
					 printf("\nCodigo da Pessoa (000-00-0000)");fflush(stdin);
					 gets(pAux.codigoPessoa);
					 printf("\nData da ultima compra: (DD/MM/AAAA)");fflush(stdin);
					 gets(pAux.ultimaCompra);
				 	 inserePessoa(lista, pAux.codigoPessoa, pAux.sexo, pAux.medicamento, pAux.ultimaCompra, pAux.pais);
					 break;
					
			case 'E':system("cls");
					 exibeLista(lista);
					 break;
			
			case 'M':printf("\nPais a ser excluido: ");
					 gets(pAux.pais);
					 excluirPais(lista,pAux.pais);
					 break;
					 
			case 'V':printf("\nMedicamento a ser excluido: ");
					 gets(pAux.medicamento);
					 excluirMedicamento(lista,pAux.medicamento);
					 break;
					 
			case 'A':system("cls");
					 printf("\nPais: ");
					 gets(pAux.pais);
					 exibirMedPais(lista,pAux.pais);
					 break;
			
			case 'B':system("cls");
					 printf("\nMedicamentos: ");
					 gets(pAux.medicamento);
					 exibirMedUsuarios(lista,pAux.medicamento);
					 break;
					 
			case 'N':system("cls");
					 relatorio(lista);
					 break;
					 
			case 27: system("cls");printf("Finalizando operacao");break;
		}
	}while(op!=27);

	getch();
}
