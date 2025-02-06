# MyLang Programming Language Documentation

Welcome to the MyLang programming language documentation. This document serves as a comprehensive guide to understanding the syntax and semantics of MyLang.

## Grammar

The language includes the following grammar rules expressed in a mathematical format using LaTeX. Here are two example rules from the grammar:

$$
\begin{align}
    \text{exit} &\to exit(\text{expr});\\
    \text{expt} &\to \text{int\_lit}
\end{align}
$$

The above rules define the following:

- **exit**: A keyword that invokes the exit function with a given expression. It is used to terminate a program or function.
- **expt**: Short for exponent, this rule translates the keyword `expt` to an integer literal.

## Examples

Below are some examples demonstrating how these grammar rules are used in MyLang:

### Example 1: Using `exit`

```mylang
exit(0);
