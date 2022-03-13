# Este exercício foi retirado do curso "Introdução à Ciência da Computação com Python Parte 1" disponibilizado pela USP de forma online e gratuita pela plataforma de e-learning Coursera
# O enunciado nos dá a seguinte definição sobre o jogo: "Nesse jogo, n peças são inicialmente dispostas numa mesa ou tabuleiro. Dois jogadores jogam  alternadamente, retirando pelo menos 1 e no máximo m peças cada um. 
# Quem tirar as últimas peças possíveis ganha o jogo." Além disso, também já é falada qual a estratégia utilizada para sempre vencer: 
# "Existe uma estratégia para ganhar o jogo que é muito simples: ela consiste em deixar sempre múltiplos de (m+1) peças ao jogador oponente."
# Sendo assim, a atividade propõem que o programador faça um algoritmo que simule a execução do jogo de forma que o computador sempre ganhe usando a estratégia mencionada.
# Ademais, o texto do exercício deixa claro, também, as funções a serem utilizadas e os comandos que o programa deve responder:
# "O programa deve implementar:
#  > Uma função computador_escolhe_jogada que recebe, como parâmetros, os números n e m descritos acima e devolve um inteiro correspondente à próxima jogada do computador 
#    (ou seja, quantas peças o computador deve retirar do tabuleiro) de acordo com a estratégia vencedora.
#  > Uma função usuario_escolhe_jogada que recebe os mesmos parâmetros, solicita que o jogador informe sua jogada e verifica se o valor informado é válido. Se o valor 
#    informado for válido, a função deve devolvê-lo; caso contrário, deve solicitar novamente ao usuário que informe uma jogada válida.
#  > Uma função partida que não recebe nenhum parâmetro, solicita ao usuário que informe os valores de n e m e inicia o jogo, alternando entre jogadas do computador e do
#    usuário (ou seja, chamadas às duas funções anteriores). A escolha da jogada inicial deve ser feita em função da estratégia vencedora, como dito anteriormente.
#    A cada jogada, deve ser impresso na tela o estado atual do jogo, ou seja, quantas peças foram removidas na última jogada e quantas restam na mesa. Quando a última 
#    peça é removida, essa função imprime na tela a mensagem "O computador ganhou!" ou "Você ganhou!" conforme o caso."
# Por fim, além de partida únicas, o programa deve ser capaz de realizar campeonatos, ou seja, fazer uma mlehor de três, para decidir qual modalidade será jogada, o usuário
# escolhe 1 para jogar uma única partida, e 2, para um campeonato (3 partidas com placar).
# Abaixo segue o código que resolve o problema e segue todas as recomendações e exigências.

# n é o número de peças
# m é o número máximo de peças que podem ser retiradas numa rodada

def main():
	print("Bem-vindo ao jogo do NIM! Escolha:\n")
	jogo=int(input("1 - para jogar uma partida isolada\n2 - para jogar um campeonato "))
	if jogo==1:
		print("\nVoce escolheu uma partida isolada!\n")
		partida()
	if jogo==2:
		print("\nVoce escolheu um campeonato!\n")
		voce=0
		computador=0
		ganhador=0
		for i in range (0,3):
			print(f"**** Rodada {i+1} ****\n")
			ganhador=partida()
			if ganhador=="computador":
				computador+=1
			else:
				voce+=1
		print("**** Final do campeonato! ****\n")
		print(f"Placar: Você {voce} X {computador} Computador")

def partida():
	n=int(input("Quantas peças? "))
	m=int(input("Limite de peças por jogada? "))
	while m<=0 or m>=n:
		m=int(input("Limite de peças por jogada? "))
	if n%(m+1)==0:
		print("\nVocê começa!\n")
		ganhador="ninguem"
		while (n>0 and ganhador=="ninguem"):
			jogada=usuario_escolhe_jogada(n, m)
			if jogada==1:
				print("\nVocê tirou uma peça.")
			else:
				print(f"Voce tirou {jogada} peças.")
			n=n-jogada
			if n==1:
				print("Agora resta apenas uma peça no tabuleiro.\n")
			if n>0 and n!=1:
				print(f"Agora restam {n} peças no tabuleiro.\n")
			if n>0:
				jogada=computador_escolhe_jogada(n, m)
				if jogada==1:
					print("O computador tirou uma peça.")
				else:
					print(f"O computador tirou {jogada} peças.")
				n=n-jogada
				if n==0:
					print("Fim do jogo! O computador ganhou!\n")
					ganhador="computador"
				if n==1:
					print("Agora resta apenas uma peça no tabuleiro.\n")
				if n>0 and n!=1:
					print(f"Agora restam {n} peças no tabuleiro.\n")
	else:
		print("\nComputador começa!\n")
		ganhador="ninguem"
		while (n>0 and ganhador=="ninguem"):
			jogada=computador_escolhe_jogada(n, m)
			if jogada==1:
				print("O computador tirou uma peça.")
			else:
				print(f"O computador tirou {jogada} peças.")
			n=n-jogada
			if n==0:
				print("Fim do jogo! O computador ganhou!\n")
				ganhador="computador"
			if n==1:
				print("Agora resta apenas uma peça no tabuleiro.\n")
			if n>0 and n!=1:
				print(f"Agora restam {n} peças no tabuleiro.\n")
			if n>0:
				jogada=usuario_escolhe_jogada(n, m)
				if jogada==1:
					print("\nVocê tirou uma peça.")
				else:
					print(f"Voce tirou {jogada} peças.")
				n=n-jogada
				if n==1:
					print("Agora resta apenas uma peça no tabuleiro.\n")
				if n>0 and n!=1:
					print(f"Agora restam {n} peças no tabuleiro.\n")
	return ganhador
	
def computador_escolhe_jogada(n, m):
	i=0
	ver=0
	while (i<m and ver==0 and i!=n):
		i+=1
		if (n-i)%(m+1)==0:
			ver=1	
	return i

def usuario_escolhe_jogada(n, m):
	jogada=int(input("Quantas peças você vai tirar? "))
	while jogada>m or jogada<=0:
		print("\nOops! Jogada inválida! Tente de novo.")
		jogada=int(input("\nQuantas peças você vai tirar? "))
	return jogada


main()
