x=int(input())
print(x)
monte=x
n100=monte//100
monte=monte%100
n50=monte//50
monte=monte%50
n20=monte//20
monte=monte%20
n10=monte//10
monte=monte%10
n5=monte//5
monte=monte%5
n2=monte//2
monte=monte%2
print(
    f"{n100} nota(s) de R$ 100,00\n"
    f"{n50} nota(s) de R$ 50,00\n"
    f"{n20} nota(s) de R$ 20,00\n"
    f"{n10} nota(s) de R$ 10,00\n"
    f"{n5} nota(s) de R$ 5,00\n"
    f"{n2} nota(s) de R$ 2,00\n"
    f"{monte} nota(s) de R$ 1,00"
)
