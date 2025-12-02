# Qin Substrate UE5 Plugin (2D Compute Shader)

This repository contains an Unreal Engine 5 plugin implementing the **Qin Substrate** —  
a 2D, mask-driven **coherence operator** designed for real-time simulation, VFX, and GPU research.

Qin is not reaction–diffusion, not CA, and not Lenia:  
it is a deterministic update rule that **tracks designer-defined masks** and resolves conflicting constraints into a *globally coherent* field using only *local* updates.

This plugin exposes Qin as a **compute shader + Blueprint node**, allowing developers to experiment with it directly inside UE5.

---

## 🔽 Download the Fixed Plugin

A fully packaged, UE5-ready version of the plugin is available here:

👉 **[Download QinSubstrate_UE5_Plugin_Fixed.zip](QinSubstrate_UE5_Plugin_Fixed.zip)**

**This is the version that UE developers should install.**  
It contains:

```
QinSubstrate/
  QinSubstrate.uplugin
  QinSubstrate_Documentation.pdf
  Source/
    QinSubstrate/
      Public/
      Private/
      Shaders/
      QinSubstrate.Build.cs
```

Drop the entire folder into:  
`YourProject/Plugins/`

---

## 🔧 What Is the Qin Substrate?

Qin evolves a 2D scalar field `u(x,y)` according to:

\[
u_{t+1} = (1 - \gamma)\,\Phi(u_t) + \gamma\,P_{M_t}
\]

Where:

- **Φ(u)** = diffusion + nonlinear tanh reaction  
- **M(x,y)** = mask texture  
- **P_M** = projection toward target values (u_on / u_off)  
- **γ** = mask influence  

This produces a stable, coherent field that:

- follows a mask  
- adapts instantly to changes  
- remains stable under conflicts  
- is trivial to parallelize on GPU  
- works as a “coherence layer” inside games/sims  

---

## 📁 Plugin Contents

- `QinSubstrate.uplugin`
- Full C++ source (Public/Private)
- Compute shader `QinCS.usf`
- Blueprint function library
- Documentation PDF
- This README

The plugin builds as a standard UE5 runtime module.

---

## 📥 Installation (UE5)

1. Unzip the plugin.
2. Place the folder:

```
YourProject/Plugins/QinSubstrate/
```

3. If C++ project → **Regenerate Project Files**.
4. Build the project.
5. Open Unreal Engine and enable:

```
Edit → Plugins → Rendering → Qin Substrate 2D
```

---

## ▶️ Basic Usage

### **1. Create two render targets**
- Format: **R8**
- Example: `RT_A`, `RT_B`
- Resolution: 256×256 or higher

### **2. Create a mask texture**
- White = region ON  
- Black = region OFF  

### **3. In Blueprint (Tick event)**

Call:

```
QinStep2D(CurrentRT, MaskTex, OutRT, Params)
```

Then swap:

```
CurrentRT <-> OutRT
```

(This is standard ping-ponging for compute shaders.)

### **4. Display the result**
- Apply RT to a material  
- Place on a plane or full-screen quad  

---

## ⚙️ Parameter Reference

| Parameter | Meaning |
|----------|---------|
| Eta      | Diffusion strength |
| Beta     | Nonlinearity slope |
| Gamma    | Mask influence (0–1) |
| UOn      | Target value when mask = white |
| UOff     | Target value when mask = black |

---

## 🧪 What You Can Do With This Plugin

- Real-time coherent fields  
- Procedural texture generation  
- Territory / influence / AI heatmaps  
- Controlled reaction-diffusion style effects  
- World-state blending  
- GPU simulation experiments  
- Niagara + compute shader hybrid FX  
- Compare Qin vs Gray-Scott vs Lenia inside UE5  

---

## 🗂 Repository Layout

```
QinSubstrate-UE5-Plugin/
 ├── QinSubstrate/               # Plugin folder
 ├── QinSubstrate_UE5_Plugin_Fixed.zip  # Download-ready plugin
 ├── QinSubstrate_Documentation.pdf
 ├── README.md
 ├── LICENSE
 └── .gitignore
```

---

## 📄 License

This project is released under the **MIT License**.

---

## 👤 Contact / Collaboration

If you build demos, integrate Qin into tools, or improve the plugin, feel free to open issues or PRs.

Contributions are welcome.
