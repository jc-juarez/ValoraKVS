// *********************
// Apexia Platforms
// Valora KVS
// Gateway
// main.go
// *********************

package main

import (
	"net/http"
	"github.com/gin-gonic/gin"
)

func main() {

	// Create a Gin router
	router := gin.Default()

	// Define a route handler
	router.GET("/", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{
			"message": "Valora KVS Gateway",
		})
	})

	// Run the server on port 8080
	router.Run(":8080")
}
