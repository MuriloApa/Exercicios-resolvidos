import math

def bhaskara(a, b, c):
    delta=b**2-4*a*c
    if delta<0 or a==0:
        print("Impossivel calcular")
    else:
        if delta==0:
            print(f"R1 = {-b/(2*a):.5f}")
            print(f"R2 = {-b/(2*a):.5f}")
        else:
            print(f"R1 = {(-b+math.sqrt(delta))/(2*a):.5f}")
            print(f"R2 = {(-b-math.sqrt(delta))/(2*a):.5f}")
            
def main():
    a,b,c=map(float, input().split(" "))
    bhaskara(a, b, c)

main()
