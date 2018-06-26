import re
########INPUT#########
MIN = " "

CONST = [
        ]

########CODE#########

# Regex to get weights from MIN
reg_weights = "( ((\+|\-)([0-9]+)) )" # replace it by .
reg_empty_weights = " x[0-9]+" # replace it by .

# Regex to get vars from MIN
reg_vars = "[0-9]+"

weights = []
lits = []

p = re.compile(reg_weights)
m = p.findall(MIN)

print 'Cost function'

for l in m:
    weights.append(int(l[0]))
print 'Weights'
print weights

MIN2 = p.sub('.',MIN)

p = re.compile(reg_empty_weights)
m = p.findall(MIN2)
MIN3 = p.sub('',MIN2)

p = re.compile(reg_vars)
m = p.findall(MIN3)

for l in m:
    lits.append(int(l))
print 'Vars'
print lits


for c in CONST:
    print 'Constraint '
    weights = []
    lits = []

    p = re.compile(reg_weights)
    m = p.findall(c)

    for l in m:
        weights.append(-int(l[0]))
    print 'Weights'
    print weights

    c2 = p.sub('.',c)

    p = re.compile(reg_empty_weights)
    m = p.findall(MIN2)
    c3 = p.sub('',c2)

    p = re.compile(reg_vars)
    m = p.findall(c3)

    for l in m:
        lits.append(int(l))
    print 'Vars'
    print lits
