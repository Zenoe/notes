# how to use:
# run with: uvicorn appqwen:app --host 0.0.0.0 --port 8003
# postman: http://ip/generate, boyd: raw, json {"prompt": "write a poem.", "max_tokens": 200}
# curl -X POST "http://localhost:8003/generate" \
#     -H "Content-Type: application/json" \
#     -d '{"prompt": "Explain the concept of large language models.", "max_tokens": 200}'


# local demo
# prompt = "Give me a short introduction to large language model."
# messages = [
#     {"role": "system", "content": "You are Qwen, created by Alibaba Cloud. You are a helpful assistant."},
#     {"role": "user", "content": prompt}
# ]
# text = tokenizer.apply_chat_template(
#     messages,
#     tokenize=False,
#     add_generation_prompt=True
# )
# model_inputs = tokenizer([text], return_tensors="pt").to(model.device)

# generated_ids = model.generate(
#     **model_inputs,
#     max_new_tokens=512
# )
# generated_ids = [
#     output_ids[len(input_ids):] for input_ids, output_ids in zip(model_inputs.input_ids, generated_ids)
# ]

# response = tokenizer.batch_decode(generated_ids, skip_special_tokens=True)[0]
# print (response)

from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from transformers import AutoModelForCausalLM, AutoTokenizer
import torch

# Initialize the FastAPI app
app = FastAPI()

# Load the model and tokenizer
model_name = "Qwen/Qwen2.5-7B-Instruct"

# download model first time when no local copy exist
# default to be ~/.cache/huggingface/
# customize cache dir:
# model = AutoModelForSequenceClassification.from_pretrained(model_name, cache_dir="path/to/my/model")
# tokenizer = AutoTokenizer.from_pretrained(model_name, cache_dir="path/to/my/model")

model = AutoModelForCausalLM.from_pretrained(
    model_name,
    torch_dtype="auto",
    device_map="auto"
)
tokenizer = AutoTokenizer.from_pretrained(model_name)

# Define the request schema
class ChatRequest(BaseModel):
    prompt: str
    max_tokens: int = 512  # Default maximum number of tokens to generate

@app.post("/generate")
async def generate_response(request: ChatRequest):
    """
    Generate a response from the Qwen model based on the input prompt.
    """
    try:
        # Prepare the input
        messages = [
            {"role": "system", "content": "You are Qwen, created by Alibaba Cloud. You are a helpful assistant."},
            {"role": "user", "content": request.prompt}
        ]
        text = tokenizer.apply_chat_template(
            messages,
            tokenize=False,
            add_generation_prompt=True
        )
        model_inputs = tokenizer([text], return_tensors="pt").to(model.device)

        # Generate response
        generated_ids = model.generate(
            **model_inputs,
            max_new_tokens=request.max_tokens
        )
        generated_ids = [
            output_ids[len(input_ids):]
            for input_ids, output_ids in zip(model_inputs.input_ids, generated_ids)
        ]
        response_text = tokenizer.batch_decode(generated_ids, skip_special_tokens=True)[0]

        return {"response": response_text}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
