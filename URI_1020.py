x=int(input())
print(
    f"{x//365} ano(s)\n"    
    f"{(x%365)//30} mes(es)\n"
    f"{(x%365)%30} dia(s)"
)
