# ============================================================
# QUANTIZED INFERENCE VERIFIER
# Run this to check quantized weights match the original model
# ============================================================
import numpy as np

SCALE = 64

def relu(x): return np.maximum(0, x)

def infer_float(feat, state):
    x = np.array(feat, dtype=np.float32)
    x = relu(state['net.0.weight'] @ x + state['net.0.bias'])
    x = relu(state['net.2.weight'] @ x + state['net.2.bias'])
    x = relu(state['net.4.weight'] @ x + state['net.4.bias'])
    x =      state['net.6.weight'] @ x + state['net.6.bias']
    return x  # logits [HOLD, BUY, SELL]

def infer_quantized(feat, state, scale):
    def quant(arr): return np.round(arr * scale).astype(np.int32)
    def relu_int(x): return np.maximum(0, x)
    x = np.round(np.array(feat) * scale).astype(np.int32)
    x = relu_int((quant(state['net.0.weight']) @ x) // scale + quant(state['net.0.bias']))
    x = relu_int((quant(state['net.2.weight']) @ x) // scale + quant(state['net.2.bias']))
    x = relu_int((quant(state['net.4.weight']) @ x) // scale + quant(state['net.4.bias']))
    x =          (quant(state['net.6.weight']) @ x) // scale + quant(state['net.6.bias'])
    return x  # integer logits

# Test with a sample feature vector
# [deviation, spread, mid_delta, ema_delta, position_norm, regime_norm,
#  dev_spread_ratio, entry_price_delta, holding_time_norm]
test_feat = [0.5, 0.1, -0.2, 0.0, 0.0, 0.667, 2.0, 0.0, 0.0]  # volatile, large deviation

import torch
ckpt = torch.load('profit_nn_out/model_best_v1_profitable.pth.tar', map_location='cpu')
state = {k: v.numpy() for k, v in ckpt['state_dict'].items()}

float_logits = infer_float(test_feat, state)
int_logits   = infer_quantized(test_feat, state, SCALE)

print('Float  logits:', float_logits)
print('Quant  logits:', int_logits / SCALE)
print('Float  action:', ['HOLD','BUY','SELL'][np.argmax(float_logits)])
print('Quant  action:', ['HOLD','BUY','SELL'][np.argmax(int_logits)])
print('Match:', np.argmax(float_logits) == np.argmax(int_logits))