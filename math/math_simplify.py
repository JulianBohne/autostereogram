import sympy as sp
sp.init_printing(use_unicode=True)

x_0, deltax, v_x, v_z, h, w_x, w_z = sp.symbols('x_0,deltax,v_x,v_z,h,w_x,w_z')

expr = (((x_0 + deltax) - (v_x - ((v_z*(x_0 + deltax)) / h)))/(w_x - ((w_z * (x_0 + deltax))/h))) - ((x_0 - (v_x - ((v_z * x_0) / h))) / (w_x - ((w_z * x_0) / h)))

simplified = sp.simplify(expr)

factored = sp.factor(simplified)

sp.print_latex(expr=factored)

