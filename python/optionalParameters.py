def funct(par1, *positionalOptionals, **keywordOptionals):
    print('---------')
    print(par1)
    print(positionalOptionals)
    print(keywordOptionals)
    print(type(positionalOptionals))
    print(type(keywordOptionals))

funct(42)
funct(42, 69)
funct(42, 69, key='666')
funct(42, key1=69, key2='666')

