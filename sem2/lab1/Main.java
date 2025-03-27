package com.example.test;

import java.util.Scanner;

public class Main {

    static int[][] topRight;
    static int[][] topLeft;
    static int[][] bottomRight;
    static int[][] bottomLeft;

    public static boolean isPowerOfTwo(int n) {
        return (n > 0) && ((n & (n - 1)) == 0);
    }

    public static boolean isSame(int[][] matrix, int raw, int column, int size){
        int first = matrix[raw][column];
        for (int i = raw; i < raw + size; i++) {
            for (int j = column; j < column + size; j++) {
                if (matrix[i][j] != first) {
                    return false;
                }
            }
        }
        return true;
    }

    public static QuadTreeNode matrixToQuadTree(int[][] matrix) {
        // Предполагаем, что матрица квадратная и размер - степень двойки
        int size = matrix.length;
        return matrixToTree(matrix, 0, 0, size);
    }

    public static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }

    public static QuadTreeNode matrixToTree(int[][] matrix, int raw, int column, int size){
        QuadTreeNode treeNode = new QuadTreeNode();

        if (isSame(matrix,raw,column, size) || size == 1){
            treeNode.setLeaf(true);
            treeNode.setValue(matrix[raw][column]);
            return treeNode;
        }

        treeNode.setTopLeft(matrixToTree(matrix, raw, column, size/2));
        treeNode.setTopRight(matrixToTree(matrix, raw, column + (size/2), size/2));
        treeNode.setBottomLeft(matrixToTree(matrix, raw + (size/2), column, size/2));
        treeNode.setBottomRight(matrixToTree(matrix, raw + (size/2), column+ (size/2), size/2));
        return treeNode;
    }

    public static void quadTreeToMatrix(QuadTreeNode node, int[][] matrix, int row, int col, int size) {
        if (node.isLeaf()) {
            for (int i = row; i < row + size; i++) {
                for (int j = col; j < col + size; j++) {
                    matrix[i][j] = node.getValue();
                }
            }
        } else {
            int newSize = size / 2;

            quadTreeToMatrix(node.getTopLeft(), matrix, row, col, newSize);
            quadTreeToMatrix(node.getTopRight(), matrix, row, col + newSize, newSize);
            quadTreeToMatrix(node.getBottomLeft(), matrix, row + newSize, col, newSize);
            quadTreeToMatrix(node.getBottomRight(), matrix, row + newSize, col + newSize, newSize);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Введите размер квадратной матрицы (n x n): ");
        int n = scanner.nextInt();

        if (n <= 0) {
            System.out.println("Размер должен быть положительным числом.");
            return;
        }

        while (!isPowerOfTwo(n)) {
            System.out.println("Размер матрицы должен быть степенью двойки (2, 4, 8, 16, ...).");
            System.out.print("Введите размер квадратной матрицы (n x n): ");
            n = scanner.nextInt();
        }

        // Создание и ввод матрицы
        int[][] matrix = new int[n][n];
        System.out.println("Введите элементы матрицы построчно:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = scanner.nextInt();
            }
        }

//        int[][] matrix = {
//                {0, 0, 100, 101},
//                {0, 0, 102, 103},
//                {90, 91, 200, 201},
//                {92, 93, 202, 203}
//        };

        System.out.println("isHomogenous(matrix2) = " + isSame(matrix, 0,0, matrix.length));

        System.out.println("Base matrix:");
        printMatrix(matrix);

        QuadTreeNode root = matrixToQuadTree(matrix);

        System.out.println("\nQuadtree:");
        printQuadTree(root, "");

        int[][] restoredMatrix = new int[matrix.length][matrix.length];
        quadTreeToMatrix(root, restoredMatrix, 0, 0, restoredMatrix.length);
        printMatrix(restoredMatrix);
    }

    public static void matrixToMatrix(int[][] matrix) {
        int size = matrix.length;


        topRight = new int[size/2][];
        topLeft = new int[size/2][];
        bottomRight = new int[size/2][];
        bottomLeft = new int[size/2][];
        for (int i = 0; i < topRight.length; i++) {
            topRight[i] = new int[size/2];
            topLeft[i] = new int[size/2];
            bottomRight[i] = new int[size/2];
            bottomLeft[i] = new int[size/2];
        }

        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++) {

                if (i < size/2 && j < size/2){
                    topRight[i][j] = matrix[i][j];
                }

                if (i < size/2 && j >= size/2){
                    topLeft[i][j % (size/2)] = matrix[i][j];
                }

                if (i >= size/2 && j >= size/2){
                    bottomRight[i % (size/2)][j % (size/2)] = matrix[i][j];
                }

                if (i >= size/2 && j < size/2){
                    bottomLeft[i % (size/2)][j] = matrix[i][j];
                }

            }
        }
    }

    public static void printQuadTree(QuadTreeNode node, String prefix) {
        if (node.isLeaf()) {
            System.out.println(prefix + "Leaf: " + node.getValue());
        } else {
            System.out.println(prefix + "Node:");
            System.out.println(prefix + "|-- TopLeft:");
            printQuadTree(node.getTopLeft(), prefix + "|   ");
            System.out.println(prefix + "|-- TopRight:");
            printQuadTree(node.getTopRight(), prefix + "|   ");
            System.out.println(prefix + "|-- BottomLeft:");
            printQuadTree(node.getBottomLeft(), prefix + "|   ");
            System.out.println(prefix + "|-- BottomRight:");
            printQuadTree(node.getBottomRight(), prefix + "    ");
        }
    }
}
