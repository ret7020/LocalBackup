from fastapi import FastAPI, File, UploadFile
import uvicorn


app = FastAPI()

@app.get("/")
async def root():
    return {"message": "API works"}


@app.patch("/commit")
async def root(file: UploadFile = File(...)):
    try:
        # FIXIT
        # Support chunks
        contents = file.file.read()
        with open(f"./Storage/{file.filename}", 'wb') as f:
            f.write(contents)
    except Exception:
        return {"message": "There was an error uploading the file"}
    finally:
        file.file.close()

    return {"message": f"Commited {file.filename}"}


if __name__ == "__main__":
    uvicorn.run("server:app", port=7777, host="0.0.0.0", reload=True, headers=[("server", "Local")])