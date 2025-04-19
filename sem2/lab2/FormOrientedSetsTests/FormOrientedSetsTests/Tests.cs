using System;
using System.IO;
using lab2;
using Xunit;

namespace Tests
{
    public class FormOrientedSetsTests
    {
        [Fact]
        public void WriteToFile_CorrectInput_WritesToFile()
        {
            // Arrange
            string input = "Test content";
            var writer = new FormOrientedSets();

            // Act
            writer.WriteToFile(input); // Запись в set.txt

            // Assert
            string fileContent = File.ReadAllText("set.txt");
            Assert.Equal(input, fileContent);
            
            File.Delete("set.txt");
        }
        
        [Fact]
        public void ReadFile_FileExists_ReturnsContent()
        {
            // Arrange
            var tempFilePath = Path.GetTempFileName(); // получаем сгенерированное название файла
            var expectedContent = "Test file content";
            File.WriteAllText(tempFilePath, expectedContent);

            var formOrientedSets = new FormOrientedSets(); // создали объект для вызова метода

            // Act
            var actualContent = formOrientedSets.ReadFile(tempFilePath);

            // Assert
            Assert.Equal(expectedContent, actualContent);

            // Cleanup
            File.Delete(tempFilePath);
        }
        
        [Fact]
        public void ReadFile_FileDoesNotExist_ReturnsEmptyString()
        {
            // Arrange
            var formOrientedSets = new FormOrientedSets();

            // Act  
            var result = formOrientedSets.ReadFile(Path.GetRandomFileName());

            // Assert
            Assert.Equal(string.Empty, result);
        }
        
        [Fact]
        public void CreateOrientedSets_ValidInput_GeneratesCombinations()
        {
            // Arrange
            var inputSet = "{a, b}";
            uint n = 2;
            var formOrientedSets = new FormOrientedSets();
            
            using (var consoleOutput = new StringWriter())
            {
                Console.SetOut(consoleOutput);

                // Act
                formOrientedSets.CreateOrientedSets(inputSet, n);

                // Assert
                var output = consoleOutput.ToString();
                Assert.Contains("{a, b}", output);
                Assert.Contains("{b, a}", output);
            }
        }

        [Fact]
        public void CreateOrientedSets_EmptySet_NoOutput()
        {
            // Arrange
            var inputSet = "{}";
            uint n = 2;
            var formOrientedSets = new FormOrientedSets();

            using (var consoleOutput = new StringWriter())
            {
                Console.SetOut(consoleOutput);

                // Act
                formOrientedSets.CreateOrientedSets(inputSet, n);

                // Assert
                var output = consoleOutput.ToString();
                Assert.Equal("", output); // Никаких комбинаций не должно быть
            }
        }
    }
}