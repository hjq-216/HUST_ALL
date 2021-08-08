postgres:
	docker run --name postgres12 -p 5432:5432 -e POSTGRES_USER=root -e POSTGRES_PASSWORD=secret -d postgres:12-alpine

createdb:
	docker exec -it postgres12 createdb --username=root --owner=root calculation

dropdb:
	docker exec -it postgres12 dropdb calculation

migrateup:
	migrate -path db/migration -database "postgresql://root:secret@localhost:5432/calculation?sslmode=disable" -verbose up

migratedown:
	migrate -path db/migration -database "postgresql://root:secret@localhost:5432/calculation?sslmode=disable" -verbose down

test:
	go test -v -cover ./...

sqlc:
	docker run --rm -v /Users/huangjunqidemac/go/src/Calculation:/src -w /src kjconroy/sqlc generate

server:
	go run main.go

.PHONY: postgres createdb dropdb migrateup migratedown test sqlc server