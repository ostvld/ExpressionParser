/*
 * Copyright 2020 Casey Sanchez
 */

#pragma once

#include <iostream>
#include <string>
#include <complex>
#include <memory>
#include <vector>
#include <map>
#include <variant>
#include <algorithm>
#include <numeric>

#include "matrix.hpp"
#include "utils.hpp"

class Node
{    
protected:
    std::variant<Matrix, std::complex<double>> m_value;
    std::vector<std::shared_ptr<Node>> m_arguments;

public:
    Node(std::variant<Matrix, std::complex<double>> const &value = 0.0);
    Node(std::initializer_list<std::shared_ptr<Node>> const &arguments);

    std::shared_ptr<Node> &Argument(size_t const &index);
    std::shared_ptr<Node> Argument(size_t const &index) const;
    std::vector<std::shared_ptr<Node>> &Arguments();
    std::vector<std::shared_ptr<Node>> Arguments() const;

    virtual std::string Type() const;

    virtual std::variant<Matrix, std::complex<double>> Value() const;

    std::complex<double> ComplexValue() const;
    Matrix MatrixValue() const;

public:
    static bool Equivalent(std::shared_ptr<Node> const &lhs_ptr, std::shared_ptr<Node> const &rhs_ptr);

    friend std::ostream &operator<<(std::ostream &ostream, Node const &node);
    friend std::ostream &operator<<(std::ostream &ostream, std::shared_ptr<Node> const &node_ptr);
};

class VariableNode : public Node
{
public:
    VariableNode(std::complex<double> const &value = 0.0);

    std::string Type() const override;

    Node &operator=(std::complex<double> const &value);
};

class ConstantNode : public Node
{
public:
    ConstantNode(std::complex<double> const &value);

    std::string Type() const override;

    Node &operator=(Node const &node) = delete;
};

class MatrixNode : public Node
{
public:
    MatrixNode(Matrix const &value);

    std::string Type() const override;
};