from dataclasses import dataclass
from dataclasses_json import dataclass_json

@dataclass_json
@dataclass
class Message:
    data: str
    desc: str
    time: int
    tag: int