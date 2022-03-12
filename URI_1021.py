
x=float(input())
print("NOTAS:")
monte=int(x*100)
n100=monte//10000
monte=monte%10000
n50=monte//5000
monte=monte%5000
n20=monte//2000
monte=monte%2000
n10=monte//1000
monte=monte%1000
n5=monte//500
monte=monte%500
n2=monte//200
monte=monte%200
m1=monte//100
monte=monte%100
m50=monte//50
monte=monte%50
m25=monte//25
monte=monte%25
m10=monte//10
monte=monte%10
m05=monte//5
monte=monte%5
m01=monte//1
print(
    f"{n100:.0f} nota(s) de R$ 100.00\n"
    f"{n50:.0f} nota(s) de R$ 50.00\n"
    f"{n20:.0f} nota(s) de R$ 20.00\n"
    f"{n10:.0f} nota(s) de R$ 10.00\n"
    f"{n5:.0f} nota(s) de R$ 5.00\n"
    f"{n2:.0f} nota(s) de R$ 2.00\n"
    f"MOEDAS:\n"
    f"{m1:.0f} moeda(s) de R$ 1.00\n"
    f"{m50:.0f} moeda(s) de R$ 0.50\n"
    f"{m25:.0f} moeda(s) de R$ 0.25\n"
    f"{m10:.0f} moeda(s) de R$ 0.10\n"
    f"{m05:.0f} moeda(s) de R$ 0.05\n"
    f"{m01:.0f} moeda(s) de R$ 0.01"
)
