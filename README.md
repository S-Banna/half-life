# Half-Life EsoLang

Half-Life is a small interpreted language for simple arithmetic and variable manipulation.
In Half-Life, your variables and statements can "reach their half-life", causing a "decay" of numbers and string values.

## Syntax

### Assume
The `assume` keyword is used to assign a value to a variable. Values can be numbers, variables, or expressions:


`assume x = 2 + 3 ` <br>
`assume y = x * 5 + 7`


### Print
The `print` keyword outputs a value. You can print expressions or string literals:

`print(x)  ` <br>
`print("This is a string")`


### Comments
Lines starting with `?` are considered comments and ignored by the interpreter:

`? this is a comment  `
`assume z = 10`

