from enum import Enum

class ReportResult(Enum):
    MISSING_FILES = 1
    COMPILATION_ERROR = 2
    TIME_LIMIT_EXCEEDED = 3
    TESTS_RUN = 4

class Report:
    def __init__(self, name, result, notes, test_scores):
        self.name = name
        self.result = result
        self.notes = notes
        self.test_scores = test_scores
    
    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return "[Name: {}, Result: {}, Notes: {}, Test Scores: {}]"\
            .format(self.name, self.result, self.notes, self.test_scores)
    
    def get_name(self):
        return self.name
    
    def get_result(self):
        return self.result
    
    def get_notes(self):
        return self.notes
    
    def get_test_scores(self):
        return self.test_scores
    
    def add_note(self, note):
        if(self.notes == ""):
            self.notes = note
        else:
            self.notes += "/n" + note
    
    def get_total(self):
        total = 0
        for key, value in self.test_scores.items():
            total += value
        return total