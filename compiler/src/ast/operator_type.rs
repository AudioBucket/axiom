#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub enum OperatorType {
    Identity,

    Add,
    Subtract,
    Multiply,
    Divide,
    Modulo,
    Power,

    BitwiseAnd,
    BitwiseOr,
    BitwiseXor,
    LogicalAnd,
    LogicalOr,
    LogicalEqual,
    LogicalNotEqual,
    LogicalGt,
    LogicalLt,
    LogicalGte,
    LogicalLte,
}
