# 📚 Database Management Systems (DBMS) – Quick Notes

## 1. DATABASE
- **Database** → Collection of related data (real-world → task).

---

## 2. DBMS
- **Definition** → Software that:
  - Stores & retrieves data securely.
  - Provides concurrency & integrity.
  - Allows applications to manipulate the database.
  - Handles user requests → OS provides data.

### Why DBMS?
Problems with File System:
- Redundancy & Inconsistency
- Difficulty in Access
- Isolation
- Integrity Issues
- Lack of Atomicity
- Concurrency Problems
- Security Concerns

---

## 3. ER DIAGRAM
- **Conceptual model** (graphical + constraints).
- Consists of **Entities, Attributes, Relationships**.
- **Primary Key (PK)** → Unique identifier (e.g., `Roll_no`).

### Entity Set
- **Strong Entity** → Has PK (underline).
- **Weak Entity** → No PK, uses Discriminator (dashed underline).

### Relationship Types
- **Unary (1)**, **Binary (2)**, **Ternary (3)**, **N-ary (n)**.

### Cardinality
- **1:1** → A ↔ B  
- **1:M** → A → many B, B → 1 A  
- **M:1** → A → 1 B, B → many A  
- **M:N** → A ↔ many B  

### Attributes
- **Simple** → Indivisible  
- **Composite** → Has sub-attributes  
- **Multi-valued** → Multiple values  
- **Derived** → Computed (e.g., `Age ← DOB`)  
- **Key** → Unique identifier  

---

## 4. CLOSURE
- Closure of attribute set → all attributes functionally dependent on it.

---

## 5. KEYS
- **Superkey** → Any set of attributes identifying a tuple.  
- **Candidate Key (CK)** → Minimal superkey.  
- **Primary Key (PK)** → Chosen CK (unique + not null).  
- **Alternate Key** → CK not chosen as PK.  
- **Foreign Key (FK)** → Attribute in R1 referencing R2.  
- **Composite Key** → PK with multiple attributes.  
- **Unique Key** → Unique values, can be NULL.  

---

## 6. FUNCTIONAL DEPENDENCY (FD)
- **α → β**
  - **Trivial** → β ⊆ α  
  - **Non-trivial** → β ⊄ α  

---

## 7. DECOMPOSITION
Splitting a relation into sub-relations.

### Properties
- **Lossless Join** → `R1 ⋈ R2 … = R`  
- **Dependency Preserving** → All FDs maintained  

### Types
- **Lossless Join** → No info lost.  
- **Lossy Join** → Some info lost.  

---

## 8. NORMALIZATION
- Reduces redundancy, improves integrity.

### Normal Forms
- **1NF** → Atomic values.  
- **2NF** → 1NF + No partial dependency.  
- **3NF** → 2NF + No transitive dependency.  
- **BCNF** → 3NF + For every FD (A→B), A is a superkey.  

---

## 9. TRANSACTION
- **Transaction** = Logical work unit = {Read + Write}.

### Transaction States
- **Active** → Executing.  
- **Partially Committed** → Last instruction done (buffer only).  
- **Committed** → Changes written to DB.  
- **Failed** → Error occurred.  
- **Aborted** → Rollback performed.  
- **Terminated** → Ended.  

### ACID Properties
- **Atomicity** → All or none.  
- **Consistency** → Integrity preserved.  
- **Isolation** → Concurrent ≈ Serial execution.  
- **Durability** → Changes permanent.  

---

## 10. SCHEDULES
- **Serial** → T1 → T2 → T3 (always consistent & safe).  
- **Non-Serial** → Interleaved (may be unsafe).  

### Serializability
- **Serializable** → Equivalent to some serial schedule.  
  - **Conflict-Serializability** → Swap non-conflicting ops.  
  - **View-Serializability** → Same final view as serial.  
- **Non-Serializable** → Not equivalent to any serial → may be inconsistent.  

### Recoverability
- **Irrecoverable** → Dirty read + commit before source.  
- **Recoverable** → Commit after source commit/abort.  

Types:
- **Cascading** → One failure → many rollbacks.  
- **Cascadeless** → Read only after writer commits/aborts.  
- **Strict** → Read/Write only after writer commits/aborts.  

---

## 11. RELATIONAL ALGEBRA
### Basic Operators
- **σ** → Selection (rows).  
- **∏** → Projection (columns).  
- **X** → Cartesian Product.  
- **U** → Union.  
- **–** → Set Difference.  
- **ρ** → Rename.  

### Extended Operators
- **∩** → Intersection.  
- **⋈c** → Conditional Join.  
- **⋈=** → Equi-Join.  
- **⋈ (Natural Join)** → Join on common attrs (no duplicates).  
- **⟕** → Left Outer Join.  
- **⟖** → Right Outer Join.  
- **⟗** → Full Outer Join.  
- **÷** → Division (A ÷ B = tuples in A related to all B).  

---

## 12. FILE STRUCTURES
- **Primary Index** → Ordered file + PK + pointer (Access ≈ log₂(Bi)+1).  
- **Clustering Index** → Ordered on non-key attribute.  
- **Secondary Index** → Alternate access path.  

---

## 13. B-TREE
- Root children: `2 → P`.  
- Internal children: `⌈P/2⌉ → P`.  
- Keys per node: `⌈P/2⌉ – 1 → P – 1`.  
- Each node = Keys + Data Pointers.  

---

## 14. B+ TREE
- **Non-leaf nodes** → Keys + Child Pointers only.  
- **Leaf nodes** → Keys + Record Pointers.  
- **Faster search** due to smaller depth than B-Tree.  

---
convert for github read.me file DATABASE → {related data → real world → task}

DBMS → {software + store/retrieve + security}
     → {programs manipulate DB}
     → {app request → OS provide data}

WHY DBMS? → {File Sys problems}
          → {Redundancy + Inconsistency + Access diff + Isolation + Integrity + Atomicity + Concurrency + Security}

---------------------------------------------------
ER DIAGRAM → {conceptual model + graphical + constraints}
           → {Entities + Attributes + Relationships}
           → PK → unique ID (Ex: Roll_no)

ENTITY SET
 ├─ Strong → {has PK → underline}
 └─ Weak   → {no PK + Discriminator → dashed underline}

RELATIONSHIP → assoc among entities
 ├─ Unary (1) ├─ Binary (2) ├─ Ternary (3) └─ N-ary (n)

CARDINALITY
 1:1 → A ↔ B
 1:M → A → many B AND B → 1 A
 M:1 → A → 1 B AND B → many A
 M:N → A ↔ many B

ATTRIBUTES
 ├─ Simple → indivisible
 ├─ Composite → {sub-attrs}
 ├─ Multi-val → multiple values
 ├─ Derived → from others (Age←DOB)
 └─ Key → unique ID
---------------------------------------------------
CLOSURE → {all attrs FD from attr set}

KEYS
 ├─ Super → {any attrs identify tuple}
 ├─ Candidate → {minimal superkey}
 ├─ Primary → {chosen CK + unique + not null}
 ├─ Alternate → {unused CK}
 ├─ Foreign → {X in R1 ref Y in R2}
 ├─ Composite → {PK with multi attrs}
 └─ Unique → {unique + non-update + may NULL}

FD: α→β
 ├─ Trivial → β⊆α
 └─ Non-trivial → β⊄α

DECOMPOSITION
 → {split relation → sub-relations}
 Properties:
   ├─ Lossless → {no info loss + R1⋈R2…=R}
   └─ Dependency Preserving → {FDs kept}
 Types:
   ├─ Lossless Join → R1⋈R2…=R
   └─ Lossy Join    → R1⋈R2…⊃R

NORMALIZATION → {reduce redundancy + integrity}
 NFs:
  1NF → atomic vals
  2NF → 1NF AND no partial dep
       (A⊂CK → B non-prime)
  3NF → 2NF AND no transitive dep
       (A not SK → B non-prime)
  BCNF → 3NF AND A→B ⇒ A is SK
---------------------------------------------------
TRANSACTION → {logical work unit = {Read+Write}}

STATES
 Active → {exec + buffer}
 Partially Cm → {last instr done + buffer only}
 Committed → {changes → DB}
 Failed → {error in Active/Partially Cm}
 Aborted → {rollback}
 Terminated → {end}

ACID
 A: Atomicity → all OR none
 C: Consistency → integrity hold
 I: Isolation → parallel = serial effect
 D: Durability → changes permanent
---------------------------------------------------
SCHEDULES
 Serial → {T1→T2→T3} → always {Consistent+Recoverable+Cascadeless+Strict}
 Non-Serial → {interleaved ops} → may OR may not safe

SERIALIZABILITY
 Serializable → {non-serial ≡ some serial}
   ├─ Conflict-Serial → swap non-conflicting ops
   └─ View-Serial    → view ≡ serial
 Non-Serializable → not ≡ any serial → may be inconsistent

RECOVERABILITY
 ├─ Irrecoverable → {dirty read + commit before src}
 └─ Recoverable   → {dirty read + commit after src commit/abort}
 Types:
   ├─ Cascading    → {failure → many rollbacks}
   ├─ Cascadeless  → {read only after writer commit/abort}
   └─ Strict       → {read+write only after writer commit/abort}
---------------------------------------------------
RELATIONAL ALGEBRA
 Basic:
   σ → Selection (rows cond)
   ∏ → Projection (cols only)
   X → Cross Product (R1×R2)
   U → Union (R1∪R2)
   – → Minus (R1–R2)
   ρ → Rename
 Extended:
   ∩ → Intersection
   ⋈c → Cond Join
   ⋈ = Equi Join
   ⋈ = Natural Join (common attrs, no dup)
   ⟕ → Left Outer Join
   ⟖ → Right Outer Join
   ⟗ → Full Outer Join
   ÷ → Division (A ÷ B = tuples in A related to all B)
---------------------------------------------------
FILE STRUCTURES
 Primary Index   → {ordered file + PK + ptr} → Access ≈ log2(Bi)+1
 Clustering Index→ {ordered on non-key attr}
 Secondary Index → {alt access path}

B-TREE
 Root children: 2→P
 Internal children: ⌈P/2⌉→P
 Keys per node: ⌈P/2⌉–1 → P–1
 Each node: {Keys + DataPtr}

B+ TREE
 Non-leaf: only keys+child ptrs
 Leaf: keys+record ptrs
 Depth ↓ → faster search than B-tree
