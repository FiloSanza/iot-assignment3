import abc
from typing import List
from message import Message

class BaseDB(abc.ABC):
    @abc.abstractmethod
    def read() -> List[Message]:
        pass

    @abc.abstractmethod
    def write(self, msg: Message):
        pass

    def write_all(self, msgs: List[Message]):
        for msg in msgs:
            self.write(msg)

class InMemoryDB(BaseDB):
    def __init__(self):
        self.db = []

    def read(self) -> List[Message]:
        return self.db

    def write(self, msg: Message):
        self.db.append(msg)