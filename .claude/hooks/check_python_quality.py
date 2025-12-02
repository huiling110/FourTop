#!/usr/bin/env python3
"""
Python Code Quality Checker for FourTop Analysis
Uses AST (Abstract Syntax Tree) for accurate analysis

Exit codes:
  0 = All checks passed
  1 = Warnings found (don't block)
  2 = Errors found (should block)
"""

import ast
import sys
from pathlib import Path
from typing import List, Tuple


class CodeQualityChecker(ast.NodeVisitor):
    """AST visitor to check code quality metrics"""

    def __init__(self):
        self.issues = []
        self.warnings = []
        self.current_class = None

    def visit_FunctionDef(self, node):
        """Check function quality metrics"""
        func_name = node.name
        context = f"{self.current_class}.{func_name}" if self.current_class else func_name

        # 1. Check function length
        if hasattr(node, 'end_lineno'):
            func_lines = node.end_lineno - node.lineno

            if func_lines > 80:
                self.issues.append(
                    f"  ❌ Function '{context}' is {func_lines} lines (max: 80)"
                )
            elif func_lines > 50:
                self.warnings.append(
                    f"  ⚠️  Function '{context}' is {func_lines} lines (recommended max: 50)"
                )

        # 2. Check nesting depth
        max_depth = self._max_nesting_depth(node)
        if max_depth > 5:
            self.issues.append(
                f"  ❌ Function '{context}' has nesting depth {max_depth} (max: 5)"
            )
        elif max_depth > 3:
            self.warnings.append(
                f"  ⚠️  Function '{context}' has nesting depth {max_depth} (recommended max: 3)"
            )

        # 3. Check complexity (number of branches)
        branches = self._count_branches(node)
        if branches > 20:
            self.issues.append(
                f"  ❌ Function '{context}' has {branches} branches (max: 20)"
            )
        elif branches > 10:
            self.warnings.append(
                f"  ⚠️  Function '{context}' has {branches} branches (recommended max: 10)"
            )

        # Continue visiting child nodes
        self.generic_visit(node)

    def visit_ClassDef(self, node):
        """Track current class context"""
        old_class = self.current_class
        self.current_class = node.name
        self.generic_visit(node)
        self.current_class = old_class

    def _max_nesting_depth(self, node, current_depth=0):
        """Calculate maximum nesting depth in a function"""
        max_depth = current_depth

        for child in ast.walk(node):
            if isinstance(child, (ast.If, ast.For, ast.While, ast.With, ast.Try)):
                # Skip the function node itself
                if child is node:
                    continue
                depth = self._node_depth(node, child)
                max_depth = max(max_depth, depth)

        return max_depth

    def _node_depth(self, root, target, current_depth=0):
        """Calculate depth of a node in the tree"""
        if root is target:
            return current_depth

        for child in ast.iter_child_nodes(root):
            if isinstance(child, (ast.If, ast.For, ast.While, ast.With, ast.Try)):
                result = self._node_depth(child, target, current_depth + 1)
                if result > 0:
                    return result
            elif child is target or any(n is target for n in ast.walk(child)):
                return current_depth

        return 0

    def _count_branches(self, node):
        """Count decision points (if, elif, for, while, try, except, with)"""
        count = 0
        for child in ast.walk(node):
            if isinstance(child, (ast.If, ast.For, ast.While, ast.ExceptHandler)):
                count += 1
            elif isinstance(child, ast.Try):
                count += len(child.handlers)
        return count


def check_file_quality(filepath: Path) -> Tuple[List[str], List[str]]:
    """
    Check Python file quality
    Returns: (issues, warnings)
    """
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            source = f.read()
    except Exception as e:
        return ([f"  ❌ Failed to read file: {e}"], [])

    # Parse the AST
    try:
        tree = ast.parse(source, filename=str(filepath))
    except SyntaxError as e:
        return ([f"  ❌ Syntax error at line {e.lineno}: {e.msg}"], [])

    # Check code quality
    checker = CodeQualityChecker()
    checker.visit(tree)

    # Check overall file size
    total_lines = len(source.splitlines())
    if total_lines > 1000:
        checker.issues.append(
            f"  ❌ File has {total_lines} lines (max: 1000)"
        )
    elif total_lines > 500:
        checker.warnings.append(
            f"  ⚠️  File has {total_lines} lines (recommended max: 500)"
        )

    return (checker.issues, checker.warnings)


def main():
    if len(sys.argv) < 2:
        print("Usage: check_python_quality.py <file.py>")
        sys.exit(1)

    filepath = Path(sys.argv[1])

    if not filepath.exists():
        print(f"❌ File not found: {filepath}")
        sys.exit(2)

    issues, warnings = check_file_quality(filepath)

    # Print results
    has_issues = len(issues) > 0
    has_warnings = len(warnings) > 0

    if has_issues:
        print("❌ Code Quality Issues Found:")
        for issue in issues:
            print(issue)

    if has_warnings:
        print("⚠️  Code Quality Warnings:")
        for warning in warnings:
            print(warning)

    if not has_issues and not has_warnings:
        print("✅ Code quality checks passed")

    # Exit codes
    if has_issues:
        print("\n💡 Tip: Break large functions into smaller, focused functions")
        print("   See: https://refactoring.guru/extract-method")
        sys.exit(2)  # Errors - should block
    elif has_warnings:
        sys.exit(1)  # Warnings - don't block
    else:
        sys.exit(0)  # All good


if __name__ == "__main__":
    main()
