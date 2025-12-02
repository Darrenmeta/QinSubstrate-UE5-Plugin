# Qin Substrate UE5 Plugin (2D Compute Shader)
This repository contains an Unreal Engine 5 plugin implementing the **Qin Substrate** — a 2D, mask-driven **coherence operator** designed for real-time simulation, VFX, and GPU research.
Qin is not reaction–diffusion, not CA, and not Lenia: it is a deterministic update rule that **tracks designer-defined masks** and resolves conflicting constraints into a *globally coherent* field using only *local* updates.
This plugin exposes Qin as a **compute shader + Blueprint node**, allowing developers to experiment with it directly inside UE5.
---
## 🔷 What Is the Qin Substrate?
Qin evolves a 2D scalar field `u(x,y)` according to:
\[
u_{t+1} = (1 - \gamma)\,\Phi(u_t) \;+\; \gamma\,P_{M_t},
\]
Where:
- **Φ(u)** = diffusion + nonlinear tanh reaction  
- **M(x,y)** = mask texture provided by the developer  
- **P_M** = projection toward mask-defined target values  
- **γ** = mask influence strength  
This produces a stable, coherent field that:
- follows a mask  
- adapts to changes in real time  
- remains stable under conflicting constraints  
- is trivial to parallelize on GPU  
- works as a “coherence layer” inside games/sims  
---
## 🔧 Plugin Contents
- `QinSubstrate.uplugin`  
- `Source/QinSubstrate/`  
  - Public/Private C++ module code  
  - Compute shader dispatch (RenderGraph)  
  - Blueprint function library  
- `Shaders/QinCS.usf` — **HLSL compute shader** implementing Qin  
- `README_QinSubstrate_UE5_2D_Full.txt` — usage instructions  
The plugin compiles as a standard UE5 runtime module.
---
## 📥 Installation
1. Place the folder here:
2. If your project uses C++, **Regenerate Project Files**.  
3. Build your project in Visual Studio or Rider.  
4. Open Unreal and enable:
---
## ▶️ Basic Usage
### **1. Create two render targets**
- Format: **R8**  
- Examples: `RT_A`, `RT_B`  
- Size: 256×256 or higher  
### **2. Create a mask texture**
- White = mask ON  
- Black = mask OFF  
### **3. On Tick (Blueprint)**
Call:
Then **swap A ↔ B** each frame:
(This ping-pong method is standard for compute shaders.)
### **4. Display the RT**
- Apply to a material  
- Put on a plane or full-screen quad  
---
## ⚙️ Parameter Reference
| Parameter | Meaning |
|----------|---------|
| Eta      | Diffusion rate |
| Beta     | Nonlinearity sharpness |
| Gamma    | Mask influence |
| UOn      | Target value for ON-mask regions |
| UOff     | Target value for OFF-mask regions |
These match the Python Qin simulations.
---
## 🧪 What You Can Do With This Plugin
- Visualize mask-driven coherent fields  
- Procedural texture / territory / AI field generation  
- Controlled reaction-diffusion alternatives  
- World-state blending layers  
- GPU simulation prototypes  
- Combine with Niagara / Material FX  
- Extend to 3D volume textures  
- Compare Qin vs Gray-Scott / Lenia inside UE5  
---
## 🗂️ Repository Structure
---
## 📄 License
The project is released under the **MIT License**, allowing commercial and non-commercial use with attribution.
---
## 👤 Contact / Collaboration
If you build demos, extend the operator, or integrate this into your own engine work, feel free to open issues or PRs. Contributions welcome.
