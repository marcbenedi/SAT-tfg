// variables "globals" (que en un futur es canviarien a parametres o de la classe)
BDDConverter
CNFConverter
VarsManager

min_value_cover = X //Valor que decidirem experimentalment

map<node, cnf> nodeToCnf
map<node, bdd> nodeToBDD
map<node, int> nodeToVar
Cnf cnffinal

void mix(Formula f)
    if f.isVar // cas Base
        BDD bdd = BDDConverter.convertFormula(f)
        nodeToBDD.insert(f,bdd)
        nodeToCnf.insert(f,emptyCnf)
        nodeToVar.insert(f,f.getValue) //quan es una variable el seu valor es la id de la

    else //cas recursiu
        mix(f.child1)
        mix(f.child2)

        int var = VarsManager.getNewVar
        nodeToVar.insert(f,var)

        int a = nodeToVar.get(child1)
        int b = nodeToVar.vat(child2)

        BDD temp = nodeToBDD.get(f.child1) f.op nodeToBDD.get(f.child2)

        BDD largetCube = temp.LargestCube()
        BDD prime = largetCube.MakePrime(temp)

        Cnf myCnf = nodeToCnf.get(child1) unio nodeToCnf.get(child2)
        switch (f.op) {
            case NOT:
            case AND:
            case OR:
                myCnf.addCnf(!var + a, !var + b, !a + !b + var)
        }
        //falta guardar myCnf???

        if (prime.property < min_value_cover)//encara haig de veure quina property es

            Formula c = getBiggestChild(f) //tria el fill que te la cnf mes gran
            int aux_var = VarsManager.newVar()

            //canviem c per la var auxiliar
            Formula newChild = Formula.newVar(aux_var)
            f.replaceChild(c,newChild)

            cnffinal.add(aux_var XNOR nodeToVar(c))
            cnffinal.add(nodeToCnf(c))

            nodeToBDD.insert(newChild,BDDConverter.convertFormula(newChild))
            temp = nodeToBDD.get(newChild) f.op nodeToBDD.get(theOtherChild)
            nodeToBDD.add(f,temp)

        else
            nodeToBDD.add(f,temp)
