from fastapi import FastAPI
from pydantic import BaseModel
from transformers import AutoModelForSequenceClassification, AutoTokenizer
import torch

# Define the request body schema
class PredictRequest(BaseModel):
    text: str

app = FastAPI()
model_name = "distilbert-base-uncased-finetuned-sst-2-english"
model = AutoModelForSequenceClassification.from_pretrained(model_name)
tokenizer = AutoTokenizer.from_pretrained(model_name)

@app.post("/predict")
async def predict(request: PredictRequest):  # Use the request body
    inputs = tokenizer(request.text, return_tensors="pt")
    with torch.no_grad():
        logits = model(**inputs).logits

    predicted_class_id = logits.argmax().item()
    return {"res": model.config.id2label[predicted_class_id]}
